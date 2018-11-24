#include "il_factor_member_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_cache.h"
#include "../../env/type_interface.h"
#include "../../env/type/class_impl.h"
#include "../../env/field.h"
#include "../../env/class_loader.h"
#include "../../env/property.h"
#include "../../env/import_manager.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_factor_impl.h"

//proto
static void ILMemberOp_check(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bool* swap);
static void ILMemberOp_check_static(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type, bool* swap);
static void ILMemberOp_check_prop(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type,bool* swap);
static void ILMemberOp_check_static_prop(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type,bool* swap);
static void ILMemberOp_typearg_delete(bc_VectorItem item);

bc_ILFactor* bc_WrapILMemberOp(bc_ILMemberOp* self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_MEMBER_OP_T);
	ret->Kind.MemberOp = self;
	self->Parent = ret;
	return ret;
}

bc_ILMemberOp* bc_NewILMemberOp(bc_StringView namev) {
	bc_ILMemberOp* ret = (bc_ILMemberOp*)MEM_MALLOC(sizeof(bc_ILMemberOp));
	ret->Source = NULL;
	ret->TypeArgs = bc_NewVector();
	ret->Name = namev;
	ret->Index = -1;
	ret->Parent = NULL;
	return ret;
}

void bc_LoadILMemberOp(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bool swap;
	bc_LoadILFactor(self->Source, env, cctx);
	ILMemberOp_check(self, env, cctx, &swap);
}

void bc_GenerateILMemberOp(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(!bc_IsStaticModifier(BC_MEMBER_MODIFIER(self->Field))) {
		bc_GenerateILFactor(self->Source, env, cctx);
	}
	bc_GenerateGetField(env->Bytecode, self->Field, self->Index);
}

bc_GenericType* bc_EvalILMemberOp(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	//ILMemberOp_checkは、
	//フィールドアクセスとプロパティアクセスを区別して、
	//プロパティなら木構造を入れ替える
	//入れ替えられたなら swap は true になる
	bool swap = false;
	bc_ILFactor* parent = self->Parent;
	ILMemberOp_check(self, env, cctx, &swap);
	if(swap) {
		return bc_EvalILFactor(parent, env, cctx);
	}
//	XSTREQ(self->name, "charArray");
	assert(self->Source != NULL);
	if(self->Field->GType->Tag == GENERIC_TYPE_TAG_NONE_T) {
		bc_GenericType* a = self->Field->GType;
		return a;
	}
	bc_GenericType* a = bc_EvalILFactor(self->Source, env, cctx);
	return bc_AtVector(a->TypeArgs, self->Field->GType->VirtualTypeIndex);
}

char* bc_ILMemberOpToString(bc_ILMemberOp* self, bc_Enviroment* env) {
	bc_Buffer* sb = bc_NewBuffer();
	char* name = bc_ILFactorToString(self->Source, env);
	bc_AppendsBuffer(sb, name);
	bc_AppendBuffer(sb, '.');
	bc_AppendsBuffer(sb, bc_Ref2Str(self->Name));
	MEM_FREE(name);
	return bc_ReleaseBuffer(sb);
}

void bc_DeleteILMemberOp(bc_ILMemberOp* self) {
	bc_DeleteILFactor(self->Source);
	bc_DeleteVector(self->TypeArgs, ILMemberOp_typearg_delete);
	MEM_FREE(self);
}
//private
static void ILMemberOp_check(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bool* swap) {
	(*swap) = false;
	if(self->Index != -1) {
		return;
	}
	//レシーバの型を取得
	bc_ILFactor* fact = self->Source;
	bc_GenericType* gtype = bc_EvalILFactor(fact, env, cctx);
	BC_ERROR();
	//レシーバの型が特定できない場合は
	//変数名を型として静的フィールドで解決する
	if(gtype == NULL) {
		return ILMemberOp_check_static(self, env, cctx, gtype, swap);
	}
	//レシーバのインスタンスフィールドを検索
	bc_Type* ctype = gtype->CoreType;
	assert(ctype->Tag == TYPE_CLASS_T);
	int temp = -1;
	self->Field = bc_FindTreeFieldClass(BC_TYPE2CLASS(ctype), self->Name, &temp);
	self->Index = temp;
	//インスタンスフィールドではない場合プロパティを検索
	if(temp == -1) {
		ILMemberOp_check_prop(self, env, cctx, gtype, swap);
	} else {
		#if defined(DEBUG)
		const char* clname = bc_Ref2Str(bc_GetClassCContext(cctx)->Name);
		#endif
		//フィールドの可視性を確認
		if(!bc_IsAccessibleFieldClass(bc_GetClassCContext(cctx), self->Field)) {
			bc_Panic(BCERROR_CAN_T_ACCESS_FIELD_T, bc_Ref2Str(bc_GetTypeName(ctype)), bc_Ref2Str(self->Field->Name));
		}
	}
}

static void ILMemberOp_check_static(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type, bool* swap) {
	bc_ILFactor* fact = self->Source;
	bc_ILVariable* ilvar = fact->Kind.Variable;
	#if defined(DEBUG)
	const char* ilvarname = bc_Ref2Str(ilvar->Kind.Static->FQCN->Name);
	#endif
	//Name.call
	//の Name を型名として解決する
	bc_GenericType* ref = bc_ResolvefImportManager(cctx->Scope, ilvar->Kind.Static->FQCN, cctx);
	receiver_type = ref;
	//Name.call
	//の call をフィールドとして解決する
	bc_Type* ccT = receiver_type->CoreType;
	assert(ccT->Tag == TYPE_CLASS_T);
	int temp = -1;
	self->Field = bc_FindTreeSFieldClass(BC_TYPE2CLASS(ccT), self->Name, &temp);
	self->Index = temp;
	if(temp == -1) {
		ILMemberOp_check_static_prop(self, env, cctx, receiver_type, swap);
	}
}

static void ILMemberOp_check_prop(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type,bool* swap) {
	int temp = -1;
	#if defined(DEBUG)
	const char* name = bc_Ref2Str(self->Name);
	#endif
	bc_Type* ctype = receiver_type->CoreType;
	bc_Property* p = bc_FindTreePropertyClass(BC_TYPE2CLASS(ctype), self->Name, &temp);
	bc_ILPropertyAccess* factp = bc_NewILPropertyAccess();
	factp->Source = self->Source;
	factp->Name = self->Name;
	factp->Property = p;
	factp->Index = temp;
	self->Source = NULL;
	self->Parent->Type = ILFACTOR_PROPERTY_T;
	self->Parent->Kind.PropertyAccess = factp;
	//プロパティの可視性を確認
	if(temp == -1) {
		bc_Panic(BCERROR_UNDEFINED_PROPERTY_T, bc_Ref2Str(bc_GetTypeName(ctype)), bc_Ref2Str(self->Name));
		bc_DeleteILFactor(factp->Source);
		factp->Source = NULL;
	} else if(!bc_IsAccessiblePropertyClass(bc_GetClassCContext(cctx), p)) {
		bc_Panic(BCERROR_CAN_T_ACCESS_PROPERTY_T, bc_Ref2Str(bc_GetTypeName(ctype)), bc_Ref2Str(p->Name));
		bc_DeleteILFactor(factp->Source);
		factp->Source = NULL;
	}
	bc_DeleteILMemberOp(self);
	(*swap) = true;
}

static void ILMemberOp_check_static_prop(bc_ILMemberOp* self, bc_Enviroment* env, bc_CallContext* cctx, bc_GenericType* receiver_type,bool* swap) {
	int temp = -1;
	bc_Type* ctype = receiver_type->CoreType;
	bc_Property* p = bc_FindTreeSPropertyClass(BC_TYPE2CLASS(ctype), self->Name, &temp);
	bc_ILPropertyAccess* factp = bc_NewILPropertyAccess();
	factp->Source = self->Source;
	factp->Name = self->Name;
	factp->Property = p;
	factp->Index = temp;
	self->Source = NULL;
	self->Parent->Type = ILFACTOR_PROPERTY_T;
	self->Parent->Kind.PropertyAccess = factp;
	//プロパティの可視性を確認
	if(!bc_IsAccessiblePropertyClass(bc_GetClassCContext(cctx), p)) {
		bc_Panic(BCERROR_CAN_T_ACCESS_PROPERTY_T, bc_Ref2Str(bc_GetTypeName(ctype)), bc_Ref2Str(p->Name));
		bc_DeleteILFactor(factp->Source);
		factp->Source = NULL;
	}
	bc_DeleteILMemberOp(self);
	assert(temp != -1);
	(*swap) = true;
	assert(temp != -1);
}


static void ILMemberOp_typearg_delete(bc_VectorItem item) {
//	GenericCache* e = (GenericCache*)item;
//	DeleteGenericCache(e);
	bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
	bc_DeleteILTypeArgument(e);
}