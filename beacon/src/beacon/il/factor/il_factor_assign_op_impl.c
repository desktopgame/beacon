#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/property.h"
#include "../../env/property_body.h"
#include "../../vm/symbol_entry.h"
#include "../../vm/generate.h"
#include "../../il/il_argument.h"
#include "../../env/field.h"

static void assign_by_namebase(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_to_field(ILAssignOp* self,ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx);
static void assign_to_Property(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_to_array(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_by_call(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void assign_by_invoke(ILFactor_invoke* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx);
static void assign_by_invoke_bound(ILFactor_invoke_bound* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx);
static void check_final(ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx);
static bool can_assign_to_field(Field* f, ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable(ILAssignOp* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable_local(ILAssignOp* self, Enviroment* env, CallContext* cctx);

ILFactor* WrapILAssignOp(ILAssignOp* self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_ASSIGN_T);
	ret->u.assign_ = self;
	return ret;
}

ILAssignOp* NewILAssignOp() {
	ILAssignOp* ret = (ILAssignOp*)MEM_MALLOC(sizeof(ILAssignOp));
	ret->Left = NULL;
	ret->Right = NULL;
	return ret;
}

void LoadILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->Left, env, cctx);
	LoadILFactor(self->Right, env, cctx);
	//voidは代入できない
	GenericType* gret = EvalILFactor(self->Right, env, cctx);
	BC_ERROR();
	if(gret->CoreType != NULL &&
	   gret->CoreType == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
}

void GenerateILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	if(self->Left->type == ILFACTOR_VARIABLE_T) {
		generate_assign_to_variable(self, env, cctx);
		//NOTE:constかどうかの検査
	//foo.bar = xxx
	} else if(self->Left->type == ILFACTOR_MEMBER_OP_T) {
		ILMemberOp* ilmem = self->Left->u.member_;
		ILFactor* ilsrc = ilmem->Source;
		if(ilsrc->type == ILFACTOR_VARIABLE_T) {
			assign_by_namebase(self, env, cctx);
		//インスタンスフィールドへの代入
		} else {
			assign_to_field(self, ilmem->Source, self->Right, ilmem->Name, env, cctx);
		}
	} else if(self->Left->type == ILFACTOR_PROPERTY_T) {
		assign_to_Property(self, env, cctx);
	} else if(self->Left->type == ILFACTOR_SUBSCRIPT_T) {
		assign_to_array(self, env, cctx);
	} else if(self->Left->type == ILFACTOR_CALL_OP_T) {
		assign_by_call(self, env, cctx);
	} else {
		assert(false);
	}
}

GenericType* EvalILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	return EvalILFactor(self->Right, env, cctx);
}

void DeleteILAssignOp(ILAssignOp* self) {
	DeleteILFactor(self->Left);
	DeleteILFactor(self->Right);
	MEM_FREE(self);
}
//private
static void assign_by_namebase(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILMemberOp* ilmem = self->Left->u.member_;
	ILFactor* ilsrc = ilmem->Source;
	ILFactor_variable* ilvar = ilsrc->u.variable_;
	//staticなフィールドへの代入
	if(ilvar->type == ILVARIABLE_TYPE_STATIC_T) {
		class_* cls = TYPE2CLASS(GetEvalTypeCContext(cctx, ilvar->u.static_->fqcn));
		int temp = -1;
		Field* sf = FindSFieldClass(cls, ilmem->Name, &temp);
		assert(temp != -1);
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutField(env->Bytecode, sf, temp);
		//指定の静的フィールドにアクセスできない
		if(!IsAccessibleFieldClass(GetClassCContext(cctx), sf)) {
			ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
				Ref2Str(GetTypeName(cls->parent)),
				Ref2Str(sf->namev)
			);
			return;
		}
		//finalなので書き込めない
		if(IsFinalModifier(sf->modifier)) {
			ThrowBCError(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(GetTypeName(cls->parent)),
				Ref2Str(sf->namev)
			);
			return;
		}
		//型の互換性を検査
		if(!can_assign_to_field(sf, self, env, cctx)) {
			return;
		}
	} else {
		assign_to_field(self, ilmem->Source, self->Right, ilmem->Name, env, cctx);
	}
}

static void assign_to_field(ILAssignOp* self, ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->CoreType);
	int temp = -1;
	Field* f = FindTreeFieldClass(cls, namev, &temp);
	assert(temp != -1);
	GenerateILFactor(receiver, env, cctx);
	GenerateILFactor(source, env, cctx);
	GeneratePutField(env->Bytecode, f, temp);
	//型の互換性を検査
	if(!can_assign_to_field(f, self, env, cctx)) {
		return;
	}
	//指定のインスタンスフィールドにアクセスできない
	if(!IsAccessibleFieldClass(GetClassCContext(cctx), f)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(GetTypeName(cls->parent)),
			Ref2Str(f->namev)
		);
	}
	check_final(receiver, source, namev, env, cctx);
}

static void assign_to_Property(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor_Property* prop = self->Left->u.prop;
	Property* pp = prop->p;
	bool is_static = IsStaticModifier(prop->p->Modifier);
	BC_ERROR();
	//プロパティへアクセスできない
	if(!IsAccessiblePropertyClass(GetClassCContext(cctx), pp)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(GetTypeName(pp->Parent)),
			Ref2Str(pp->Name)
		);
		return;
	}
	if(!IsAccessiblePropertyAccessorClass(GetClassCContext(cctx), pp->Set)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(GetTypeName(pp->Parent)),
			Ref2Str(pp->Name)
		);
		return;
	}
	if(DistanceGenericType(prop->p->GType, EvalILFactor(self->Right, env, cctx), cctx) < 0) {
		ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T,
			Ref2Str(GetTypeName(prop->p->Parent)),
			Ref2Str(prop->p->Name)
		);
		return;
	}
	//省略記法なら初期化されてるかチェック
	if(pp->IsShort && !IsStaticModifier(pp->Modifier)) {
		check_final(prop->fact, self->Right, prop->p->SourceRef->namev, env, cctx);
	}
	BC_ERROR();
	if(!is_static) {
		GenerateILFactor(prop->fact, env, cctx);
	}
	GenerateILFactor(self->Right, env, cctx);
	GeneratePutProperty(env->Bytecode, pp, prop->index);
}

static void assign_to_array(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor_subscript* subs = self->Left->u.subscript;
	GenerateILFactor(subs->receiver, env, cctx);
	GenerateILFactor(subs->pos, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, subs->operator_index);
}

static void assign_by_call(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor_call_op* call = self->Left->u.call_;
	if(call->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ThrowBCError(
			BCERROR_LHS_IS_NOT_SUBSCRIPT_T,
			Ref2Str(call->u.invoke_static_->namev)
		);
		return;
	}
	if(call->type == ILCALL_TYPE_INVOKE_T) {
		assign_by_invoke(call->u.invoke_, self->Right, env, cctx);
	} else if(call->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		assign_by_invoke_bound(call->u.invoke_bound_, self->Right, env, cctx);
	} else {
		assert(false);
	}
}

static void assign_by_invoke(ILFactor_invoke* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx) {
	int temp = -1;
	if(lhs->tag != INSTANCE_INVOKE_SUBSCRIPT_T) {
		ThrowBCError(BCERROR_ASSIGN_TO_INVOKE_T,
			Ref2Str(lhs->namev)
		);
		return;
	}
	FindSetILInvoke(lhs, rhs, env, cctx, &temp);
	for(int i=0; i<lhs->args->Length; i++) {
		ILArgument* arg = AtVector(lhs->args, i);
		GenerateILFactor(arg->Factor, env, cctx);
	}
	GenerateILFactor(rhs, env, cctx);
	GenerateILFactor(lhs->receiver, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, temp);
	AddOpcodeBuf(env->Bytecode, OP_NOP);
}

static void assign_by_invoke_bound(ILFactor_invoke_bound* lhs, ILFactor* rhs, Enviroment* env, CallContext* cctx) {
	int temp = -1;
	FindSetILInvokeBound(lhs, rhs, env, cctx, &temp);
	assert(lhs->args->Length == 1);
	for(int i=0; i<lhs->args->Length; i++) {
		ILArgument* arg = AtVector(lhs->args, i);
		GenerateILFactor(arg->Factor, env, cctx);
	}
	GenerateILFactor(rhs, env, cctx);
	//GenerateILFactor(lhs->receiver, env, cctx);
	subscript_descriptor subs = lhs->u.subscript;
	if(subs.tag == SUBSCRIPT_LOCAL_T) {
		AddOpcodeBuf(env->Bytecode, OP_LOAD);
		AddOpcodeBuf(env->Bytecode, subs.index);
	} else if(subs.tag == SUBSCRIPT_FIELD_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetField(env->Bytecode, subs.u.fi, subs.index);
	} else if(subs.tag == SUBSCRIPT_PROPERTY_T) {
		AddOpcodeBuf(env->Bytecode, OP_THIS);
		GenerateGetProperty(env->Bytecode, subs.u.prop, subs.index);
	}
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, temp);
}

static bool can_assign_to_field(Field* f, ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(self->Right, env, cctx);
	int dist = DistanceGenericType(f->gtype, gt, cctx);
	if(dist >= 0) {
		return true;
	} else {
		ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_FIELD_T,
			Ref2Str(GetTypeName(f->parent)),
			Ref2Str(f->namev)
		);
		return false;
	}
}

static void check_final(ILFactor* receiver, ILFactor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	GenericType* gt = EvalILFactor(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->CoreType);
	int temp = -1;
	Field* f = FindTreeFieldClass(cls, namev, &temp);
	assert(temp != -1);
	//コンストラクタ以外の場所では finalフィールドは初期化できない
	if(cctx->Tag != CALL_CTOR_T) {
		//finalなので書き込めない
		if(IsFinalModifier(f->modifier)) {
			ThrowBCError(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(GetTypeName(cls->parent)),
				Ref2Str(f->namev)
			);
		}
	} else {
		//コンストラクタであっても static final の場合は書き込めない
		if(IsFinalModifier(f->modifier) &&
		   IsStaticModifier(f->modifier)) {
			ThrowBCError(BCERROR_ASSIGN_TO_FINAL_FIELD_T,
				Ref2Str(GetTypeName(cls->parent)),
				Ref2Str(f->namev)
			);
		}
		f->not_initialized_at_ctor = true;
	}

}

static void generate_assign_to_variable(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	assert(self->Left->type == ILFACTOR_VARIABLE_T);
	ILFactor_variable* ilvar = self->Left->u.variable_;
	if(ilvar->type == ILVARIABLE_TYPE_LOCAL_T) {
		generate_assign_to_variable_local(self, env, cctx);
	}
}

static void generate_assign_to_variable_local(ILAssignOp* self, Enviroment* env, CallContext* cctx) {
	ILFactor_variable* ilvar = self->Left->u.variable_;
	ILFactor_variable_local* illoc = ilvar->u.local_;
	//src のような名前がローカル変数を示す場合
	if(illoc->type == VARIABLE_LOCAL_SCOPE_T) {
		#if defined(DEBUG)
		const char* vname = Ref2Str(ilvar->fqcn->Name);
		#endif
		SymbolEntry* e = EntrySymbolTable(env->Symboles, NULL, ilvar->fqcn->Name);
		//e==NULL の時変数がない
		GenerateILFactor(self->Right, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_STORE);
		AddOpcodeBuf(env->Bytecode, e->Index);
		if(DistanceGenericType(e->GType, EvalILFactor(self->Right, env, cctx), cctx) < 0) {
			ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
				Ref2Str(ilvar->fqcn->Name)
			);
			return;
		}
	//src のような名前がフィールドを示す場合
	} else if(illoc->type == VARIABLE_LOCAL_FIELD_T) {
		int temp = -1;
		Field* f = FindTreeFieldClass(GetClassCContext(cctx), illoc->namev, &temp);
		if(temp == -1) {
			f = FindTreeSFieldClass(GetClassCContext(cctx), illoc->namev, &temp);
		}
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!IsStaticModifier(f->modifier) &&
		    IsStaticCContext(cctx)) {
			ThrowBCError(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
				Ref2Str(GetTypeName(f->parent)),
				Ref2Str(f->namev)
			);
			return;
		}
		if(!IsStaticModifier(f->modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutField(env->Bytecode, f, temp);
		//assert(!IsStaticModifier(f->modifier));
	//src のような名前がプロパティを示す場合
	} else if(illoc->type == VARIABLE_LOCAL_PROPERTY_T) {
		int temp = -1;
		Property* p = FindTreePropertyClass(GetClassCContext(cctx), illoc->namev, &temp);
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!IsStaticModifier(p->Modifier) &&
		    IsStaticCContext(cctx)) {
			ThrowBCError(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
				Ref2Str(GetTypeName(p->Parent)),
				Ref2Str(p->Name)
			);
			return;
		}
		if(!IsStaticModifier(p->Modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateILFactor(self->Right, env, cctx);
		GeneratePutProperty(env->Bytecode, p, temp);
		assert(!IsStaticModifier(p->Modifier));
	}
}