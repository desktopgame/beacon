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
static void ILFactor_member_op_check(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, bool* swap);
static void ILFactor_member_op_check_static(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type, bool* swap);
static void ILFactor_member_op_check_prop(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type,bool* swap);
static void ILFactor_member_op_check_static_prop(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type,bool* swap);
static void ILFactor_member_op_typearg_delete(VectorItem item);

ILFactor* WrapILMemberOp(ILFactor_member_op* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_MEMBER_OP_T);
	ret->u.member_ = self;
	self->parent = ret;
	return ret;
}

ILFactor_member_op* NewILMemberOp(StringView namev) {
	ILFactor_member_op* ret = (ILFactor_member_op*)MEM_MALLOC(sizeof(ILFactor_member_op));
	ret->fact = NULL;
	ret->type_args = NewVector();
	ret->namev = namev;
	ret->index = -1;
	ret->parent = NULL;
	return ret;
}

void LoadILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx) {
	bool swap;
	LoadILFactor(self->fact, env, cctx);
	ILFactor_member_op_check(self, env, cctx, &swap);
}

void GenerateILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx) {
	if(!IsStaticModifier(self->f->modifier)) {
		GenerateILFactor(self->fact, env, cctx);
	}
	GenerateGetField(env->Bytecode, self->f, self->index);
}

GenericType* EvalILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx) {
	//ILFactor_member_op_checkは、
	//フィールドアクセスとプロパティアクセスを区別して、
	//プロパティなら木構造を入れ替える
	//入れ替えられたなら swap は true になる
	bool swap = false;
	ILFactor* parent = self->parent;
	ILFactor_member_op_check(self, env, cctx, &swap);
	if(swap) {
		return EvalILFactor(parent, env, cctx);
	}
//	XSTREQ(self->name, "charArray");
	assert(self->fact != NULL);
	if(self->f->gtype->Tag == GENERIC_TYPE_TAG_NONE_T) {
		GenericType* a = self->f->gtype;
		return a;
	}
	GenericType* a = EvalILFactor(self->fact, env, cctx);
	return AtVector(a->TypeArgs, self->f->gtype->VirtualTypeIndex);
}

char* ILMemberOpToString(ILFactor_member_op* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* name = ILFactorToString(self->fact, env);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILMemberOp(ILFactor_member_op* self) {
	DeleteILFactor(self->fact);
	DeleteVector(self->type_args, ILFactor_member_op_typearg_delete);
	MEM_FREE(self);
}
//private
static void ILFactor_member_op_check(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, bool* swap) {
	(*swap) = false;
	if(self->index != -1) {
		return;
	}
	//レシーバの型を取得
	ILFactor* fact = self->fact;
	GenericType* gtype = EvalILFactor(fact, env, cctx);
	BC_ERROR();
	//レシーバの型が特定できない場合は
	//変数名を型として静的フィールドで解決する
	if(gtype == NULL) {
		return ILFactor_member_op_check_static(self, env, cctx, gtype, swap);
	}
	//レシーバのインスタンスフィールドを検索
	type* ctype = gtype->CoreType;
	assert(ctype->tag == TYPE_CLASS_T);
	int temp = -1;
	self->f = FindTreeFieldClass(TYPE2CLASS(ctype), self->namev, &temp);
	self->index = temp;
	//インスタンスフィールドではない場合プロパティを検索
	if(temp == -1) {
		ILFactor_member_op_check_prop(self, env, cctx, gtype, swap);
	} else {
		#if defined(DEBUG)
		const char* clname = Ref2Str(GetClassCContext(cctx)->namev);
		#endif
		//フィールドの可視性を確認
		if(!IsAccessibleFieldClass(GetClassCContext(cctx), self->f)) {
			ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T, Ref2Str(GetTypeName(ctype)), Ref2Str(self->f->namev));
		}
	}
}

static void ILFactor_member_op_check_static(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type, bool* swap) {
	ILFactor* fact = self->fact;
	ILFactor_variable* ilvar = fact->u.variable_;
	#if defined(DEBUG)
	const char* ilvarname = Ref2Str(ilvar->u.static_->fqcn->Name);
	#endif
	//Name.call
	//の Name を型名として解決する
	GenericType* ref = ResolvefImportManager(cctx->Scope, ilvar->u.static_->fqcn, cctx);
	receiver_type = ref;
	//Name.call
	//の call をフィールドとして解決する
	type* ccT = receiver_type->CoreType;
	assert(ccT->tag == TYPE_CLASS_T);
	int temp = -1;
	self->f = FindTreeSFieldClass(TYPE2CLASS(ccT), self->namev, &temp);
	self->index = temp;
	if(temp == -1) {
		ILFactor_member_op_check_static_prop(self, env, cctx, receiver_type, swap);
	}
}

static void ILFactor_member_op_check_prop(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type,bool* swap) {
	int temp = -1;
	#if defined(DEBUG)
	const char* name = Ref2Str(self->namev);
	#endif
	type* ctype = receiver_type->CoreType;
	Property* p = FindTreePropertyClass(TYPE2CLASS(ctype), self->namev, &temp);
	ILFactor_Property* factp = ILFactor_Property_new();
	factp->fact = self->fact;
	factp->namev = self->namev;
	factp->p = p;
	factp->index = temp;
	self->fact = NULL;
	self->parent->type = ILFACTOR_PROPERTY_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(temp == -1) {
		ThrowBCError(BCERROR_UNDEFINED_PROPERTY_T, Ref2Str(GetTypeName(ctype)), Ref2Str(self->namev));
		DeleteILFactor(factp->fact);
		factp->fact = NULL;
	} else if(!IsAccessiblePropertyClass(GetClassCContext(cctx), p)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(GetTypeName(ctype)), Ref2Str(p->Name));
		DeleteILFactor(factp->fact);
		factp->fact = NULL;
	}
	DeleteILMemberOp(self);
	(*swap) = true;
}

static void ILFactor_member_op_check_static_prop(ILFactor_member_op* self, Enviroment* env, CallContext* cctx, GenericType* receiver_type,bool* swap) {
	int temp = -1;
	type* ctype = receiver_type->CoreType;
	Property* p = FindTreeSPropertyClass(TYPE2CLASS(ctype), self->namev, &temp);
	ILFactor_Property* factp = ILFactor_Property_new();
	factp->fact = self->fact;
	factp->namev = self->namev;
	factp->p = p;
	factp->index = temp;
	self->fact = NULL;
	self->parent->type = ILFACTOR_PROPERTY_T;
	self->parent->u.prop = factp;
	//プロパティの可視性を確認
	if(!IsAccessiblePropertyClass(GetClassCContext(cctx), p)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(GetTypeName(ctype)), Ref2Str(p->Name));
		DeleteILFactor(factp->fact);
		factp->fact = NULL;
	}
	DeleteILMemberOp(self);
	assert(temp != -1);
	(*swap) = true;
	assert(temp != -1);
}


static void ILFactor_member_op_typearg_delete(VectorItem item) {
//	GenericCache* e = (GenericCache*)item;
//	DeleteGenericCache(e);
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}