#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../il_type_argument.h"
#include "../../../env/field.h"
#include "../../../env/property.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/generate.h"
#include "../../../vm/symbol_entry.h"
#include "../../il_argument.h"
#include <string.h>
#include <stdio.h>

static void DeleteILVariableLocal_typeargs(VectorItem item);
static void LoadILVariableLocalImpl(ILVariableLocal * self, Enviroment * env, CallContext* cctx);
static void LoadILVariableLocal_field(ILVariableLocal * self, Enviroment * env, CallContext* cctx);
static void LoadILVariableLocal_Property(ILVariableLocal * self, Enviroment * env, CallContext* cctx);
static void set_gtype(ILVariableLocal * self, GenericType* gt);

ILVariableLocal* NewILVariableLocal(StringView namev) {
	ILVariableLocal* ret = (ILVariableLocal*)MEM_MALLOC(sizeof(ILVariableLocal));
	ret->Name = namev;
	ret->Type = VARIABLE_LOCAL_UNDEFINED_T;
	ret->TypeArgs = NULL;
	ret->GType = NULL;
	return ret;
}

void GenerateILVariableLocal(ILVariableLocal* self, Enviroment* env, CallContext* cctx) {
	LoadILVariableLocal(self, env, cctx);
	assert(self->Type != VARIABLE_LOCAL_UNDEFINED_T);
	if(self->Type == VARIABLE_LOCAL_SCOPE_T) {
		//より深くネストされたブロックで定義された変数
		if(self->Kind.Entry->ScopeDepth > env->Symboles->ScopeDepth) {
			ThrowBCError(
				BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T,
				Ref2Str(self->Name)
			);
			return;
		}
		AddOpcodeBuf(env->Bytecode, (VectorItem)OP_LOAD);
		AddOpcodeBuf(env->Bytecode, (VectorItem)self->Kind.Entry->Index);
	} else if(self->Type == VARIABLE_LOCAL_FIELD_T) {
		Field* f = self->Kind.FieldI.Field;
		if(!IsStaticModifier(f->modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateGetField(env->Bytecode, f, self->Kind.FieldI.Index);
	} else if(self->Type == VARIABLE_LOCAL_PROPERTY_T) {
		Property* p = self->Kind.PropertyI.Property;
		if(!IsStaticModifier(p->Modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateGetProperty(env->Bytecode, p, self->Kind.PropertyI.Index);
	}
}

void LoadILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx) {
	if(self->Type != VARIABLE_LOCAL_UNDEFINED_T) {
		return;
	}
	LoadILVariableLocalImpl(self, env, cctx);
}

GenericType* EvalILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx) {
	LoadILVariableLocal(self, env, cctx);
	assert(self->Type != VARIABLE_LOCAL_UNDEFINED_T);
	return self->GType;
}

char* ILVariableLocalToString(ILVariableLocal * self, Enviroment * env) {
	return Strdup(Ref2Str(self->Name));
}

void DeleteILVariableLocal(ILVariableLocal* self) {
	DeleteVector(self->TypeArgs, DeleteILVariableLocal_typeargs);
//	generic_DeleteType(self->GType);
	MEM_FREE(self);
}
//private
static void DeleteILVariableLocal_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}

static void LoadILVariableLocalImpl(ILVariableLocal * self, Enviroment * env, CallContext* cctx) {
	//NOTE:変数宣言の後にその変数を使用する場合、
	//factorはload時点でシンボルエントリーを取得しようとするが、
	//stmtはgenerate時点でシンボルテーブルへ書き込むので、
	//NULLになることがある。
	self->Type = VARIABLE_LOCAL_SCOPE_T;
	SymbolEntry* ent = EntrySymbolTable(env->Symboles, NULL, self->Name);
	//ローカル変数として解決出来なかったので、
	//フィールドとして解決する
	if(ent == NULL) {
		LoadILVariableLocal_field(self, env, cctx);
	} else {
		self->Kind.Entry = ent;
		self->GType = ent->GType;
	}
}

static void LoadILVariableLocal_field(ILVariableLocal * self, Enviroment * env, CallContext* cctx) {
	//対応するフィールドを検索
	self->Type = VARIABLE_LOCAL_FIELD_T;
	//NOTE:トップレベルではここが空なので、
	//定義されていない変数とみなせる？
	Type* tp = GetTypeCContext(cctx);
	if(tp->Tag == TYPE_INTERFACE_T/* この条件は構文規則からして満たさないはず */) {
		ThrowBCError(BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T, Ref2Str(self->Name));
		return;
	}
	int temp = -1;
#if defined(_MSC_VER)
	FieldWithIndex fwi;
#else
	FieldWithIndex fwi = {};
#endif
	Field* f = FindTreeFieldClass(TYPE2CLASS(tp), self->Name, &temp);
	fwi.Field = f;
	fwi.Index = temp;
	self->Type = VARIABLE_LOCAL_FIELD_T;
	if(temp == -1) {
		f = FindTreeSFieldClass(TYPE2CLASS(tp), self->Name, &temp);
		fwi.Field = f;
		fwi.Index = temp;
		self->Type = VARIABLE_LOCAL_FIELD_T;
	}
	self->Kind.FieldI = fwi;
	if(temp == -1) {
		LoadILVariableLocal_Property(self, env, cctx);
		return;
	//フィールドが見つかったなら可視性を確認する
	} else if(!IsAccessibleFieldClass(GetClassCContext(cctx), f)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T, Ref2Str(GetClassCContext(cctx)->namev), Ref2Str(f->namev));
		return;
	}
	set_gtype(self, f->gtype);
}

static void LoadILVariableLocal_Property(ILVariableLocal * self, Enviroment * env, CallContext* cctx) {
	int temp = -1;
	Type* tp = GetTypeCContext(cctx);
	Property* p = FindTreePropertyClass(TYPE2CLASS(tp), self->Name, &temp);
	if(temp == -1) {
		p = FindTreeSPropertyClass(TYPE2CLASS(tp), self->Name, &temp);
	}
	if(temp == -1) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(GetTypeName(tp)), Ref2Str(self->Name));
		return;
	}
#if defined(_MSC_VER)
	PropertyWithIndex pwi;
#else
	PropertyWithIndex pwi = {};
#endif
	pwi.Property = p;
	pwi.Index = temp;
	self->Type = VARIABLE_LOCAL_PROPERTY_T;
	self->Kind.PropertyI = pwi;
	//プロパティにアクセスできない
	if(!IsAccessiblePropertyClass(TYPE2CLASS(tp), p)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_PROPERTY_T, Ref2Str(GetTypeName(tp)), Ref2Str(p->Name));
	}
	set_gtype(self, p->GType);
}

static void set_gtype(ILVariableLocal * self, GenericType* gt) {
	//GenericType* gt = f->GTypeype;
	//virtual_type vt = f->vtype;
	if(gt->Tag == GENERIC_TYPE_TAG_NONE_T) {
		self->GType = gt;
	} else if(gt->Tag == GENERIC_TYPE_TAG_CLASS_T) {
		self->GType = generic_NewType(NULL);
		self->GType->Tag = GENERIC_TYPE_TAG_CLASS_T;
		self->GType->VirtualTypeIndex = gt->VirtualTypeIndex;
	} else if(gt->Tag == GENERIC_TYPE_TAG_METHOD_T) {
		self->GType = generic_NewType(NULL);
		self->GType->Tag = GENERIC_TYPE_TAG_METHOD_T;
		self->GType->VirtualTypeIndex = gt->VirtualTypeIndex;
	}
}
//private