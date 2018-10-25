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

static void assign_by_namebase(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void assign_to_field(il_factor_assign_op* self,il_factor* receiver, il_factor* source, StringView namev, Enviroment* env, CallContext* cctx);
static void assign_to_property(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void assign_to_array(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void assign_by_call(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void assign_by_invoke(il_factor_invoke* lhs, il_factor* rhs, Enviroment* env, CallContext* cctx);
static void assign_by_invoke_bound(il_factor_invoke_bound* lhs, il_factor* rhs, Enviroment* env, CallContext* cctx);
static void check_final(il_factor* receiver, il_factor* source, StringView namev, Enviroment* env, CallContext* cctx);
static bool can_assign_to_field(field* f, il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);
static void generate_assign_to_variable_local(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);

il_factor* WrapILAssignOp(il_factor_assign_op* self) {
	il_factor* ret = il_factor_new(ILFACTOR_ASSIGN_T);
	ret->u.assign_ = self;
	return ret;
}

il_factor_assign_op* NewILAssignOp() {
	il_factor_assign_op* ret = (il_factor_assign_op*)MEM_MALLOC(sizeof(il_factor_assign_op));
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void LoadILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->left, env, cctx);
	LoadILFactor(self->right, env, cctx);
	//voidは代入できない
	generic_type* gret = EvalILFactor(self->right, env, cctx);
	BC_ERROR();
	if(gret->core_type != NULL &&
	   gret->core_type == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
}

void GenerateILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	if(self->left->type == ILFACTOR_VARIABLE_T) {
		generate_assign_to_variable(self, env, cctx);
		//NOTE:constかどうかの検査
	//foo.bar = xxx
	} else if(self->left->type == ILFACTOR_MEMBER_OP_T) {
		il_factor_member_op* ilmem = self->left->u.member_;
		il_factor* ilsrc = ilmem->fact;
		if(ilsrc->type == ILFACTOR_VARIABLE_T) {
			assign_by_namebase(self, env, cctx);
		//インスタンスフィールドへの代入
		} else {
			assign_to_field(self, ilmem->fact, self->right, ilmem->namev, env, cctx);
		}
	} else if(self->left->type == ILFACTOR_PROPERTY_T) {
		assign_to_property(self, env, cctx);
	} else if(self->left->type == ILFACTOR_SUBSCRIPT_T) {
		assign_to_array(self, env, cctx);
	} else if(self->left->type == ILFACTOR_CALL_OP_T) {
		assign_by_call(self, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* EvalILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	return EvalILFactor(self->right, env, cctx);
}

void DeleteILAssignOp(il_factor_assign_op* self) {
	DeleteILFactor(self->left);
	DeleteILFactor(self->right);
	MEM_FREE(self);
}
//private
static void assign_by_namebase(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	il_factor_member_op* ilmem = self->left->u.member_;
	il_factor* ilsrc = ilmem->fact;
	il_factor_variable* ilvar = ilsrc->u.variable_;
	//staticなフィールドへの代入
	if(ilvar->type == ILVARIABLE_TYPE_STATIC_T) {
		class_* cls = TYPE2CLASS(GetEvalTypeCContext(cctx, ilvar->u.static_->fqcn));
		int temp = -1;
		field* sf = FindSFieldClass(cls, ilmem->namev, &temp);
		assert(temp != -1);
		GenerateILFactor(self->right, env, cctx);
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
		assign_to_field(self, ilmem->fact, self->right, ilmem->namev, env, cctx);
	}
}

static void assign_to_field(il_factor_assign_op* self, il_factor* receiver, il_factor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	generic_type* gt = EvalILFactor(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->core_type);
	int temp = -1;
	field* f = FindTreeFieldClass(cls, namev, &temp);
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

static void assign_to_property(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	il_factor_property* prop = self->left->u.prop;
	property* pp = prop->p;
	bool is_static = IsStaticModifier(prop->p->modifier);
	BC_ERROR();
	//プロパティへアクセスできない
	if(!IsAccessiblePropertyClass(GetClassCContext(cctx), pp)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(GetTypeName(pp->parent)),
			Ref2Str(pp->namev)
		);
		return;
	}
	if(!IsAccessiblePropertyAccessorClass(GetClassCContext(cctx), pp->set)) {
		ThrowBCError(BCERROR_CAN_T_ACCESS_FIELD_T,
			Ref2Str(GetTypeName(pp->parent)),
			Ref2Str(pp->namev)
		);
		return;
	}
	if(DistanceGenericType(prop->p->gtype, EvalILFactor(self->right, env, cctx), cctx) < 0) {
		ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T,
			Ref2Str(GetTypeName(prop->p->parent)),
			Ref2Str(prop->p->namev)
		);
		return;
	}
	//省略記法なら初期化されてるかチェック
	if(pp->is_short && !IsStaticModifier(pp->modifier)) {
		check_final(prop->fact, self->right, prop->p->source_ref->namev, env, cctx);
	}
	BC_ERROR();
	if(!is_static) {
		GenerateILFactor(prop->fact, env, cctx);
	}
	GenerateILFactor(self->right, env, cctx);
	GeneratePutProperty(env->Bytecode, pp, prop->index);
}

static void assign_to_array(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	il_factor_subscript* subs = self->left->u.subscript;
	GenerateILFactor(subs->receiver, env, cctx);
	GenerateILFactor(subs->pos, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	AddOpcodeBuf(env->Bytecode, subs->operator_index);
}

static void assign_by_call(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	il_factor_call_op* call = self->left->u.call_;
	if(call->type == ILCALL_TYPE_INVOKE_STATIC_T) {
		ThrowBCError(
			BCERROR_LHS_IS_NOT_SUBSCRIPT_T,
			Ref2Str(call->u.invoke_static_->namev)
		);
		return;
	}
	if(call->type == ILCALL_TYPE_INVOKE_T) {
		assign_by_invoke(call->u.invoke_, self->right, env, cctx);
	} else if(call->type == ILCALL_TYPE_INVOKE_BOUND_T) {
		assign_by_invoke_bound(call->u.invoke_bound_, self->right, env, cctx);
	} else {
		assert(false);
	}
}

static void assign_by_invoke(il_factor_invoke* lhs, il_factor* rhs, Enviroment* env, CallContext* cctx) {
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

static void assign_by_invoke_bound(il_factor_invoke_bound* lhs, il_factor* rhs, Enviroment* env, CallContext* cctx) {
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

static bool can_assign_to_field(field* f, il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	generic_type* gt = EvalILFactor(self->right, env, cctx);
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

static void check_final(il_factor* receiver, il_factor* source, StringView namev, Enviroment* env, CallContext* cctx) {
	generic_type* gt = EvalILFactor(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->core_type);
	int temp = -1;
	field* f = FindTreeFieldClass(cls, namev, &temp);
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

static void generate_assign_to_variable(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	assert(self->left->type == ILFACTOR_VARIABLE_T);
	il_factor_variable* ilvar = self->left->u.variable_;
	if(ilvar->type == ILVARIABLE_TYPE_LOCAL_T) {
		generate_assign_to_variable_local(self, env, cctx);
	}
}

static void generate_assign_to_variable_local(il_factor_assign_op* self, Enviroment* env, CallContext* cctx) {
	il_factor_variable* ilvar = self->left->u.variable_;
	il_factor_variable_local* illoc = ilvar->u.local_;
	//src のような名前がローカル変数を示す場合
	if(illoc->type == VARIABLE_LOCAL_SCOPE_T) {
		#if defined(DEBUG)
		const char* vname = Ref2Str(ilvar->fqcn->Name);
		#endif
		SymbolEntry* e = EntrySymbolTable(env->Symboles, NULL, ilvar->fqcn->Name);
		//e==NULL の時変数がない
		GenerateILFactor(self->right, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_STORE);
		AddOpcodeBuf(env->Bytecode, e->Index);
		if(DistanceGenericType(e->GType, EvalILFactor(self->right, env, cctx), cctx) < 0) {
			ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
				Ref2Str(ilvar->fqcn->Name)
			);
			return;
		}
	//src のような名前がフィールドを示す場合
	} else if(illoc->type == VARIABLE_LOCAL_FIELD_T) {
		int temp = -1;
		field* f = FindTreeFieldClass(GetClassCContext(cctx), illoc->namev, &temp);
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
		GenerateILFactor(self->right, env, cctx);
		GeneratePutField(env->Bytecode, f, temp);
		//assert(!IsStaticModifier(f->modifier));
	//src のような名前がプロパティを示す場合
	} else if(illoc->type == VARIABLE_LOCAL_PROPERTY_T) {
		int temp = -1;
		property* p = FindTreePropertyClass(GetClassCContext(cctx), illoc->namev, &temp);
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!IsStaticModifier(p->modifier) &&
		    IsStaticCContext(cctx)) {
			ThrowBCError(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
				Ref2Str(GetTypeName(p->parent)),
				Ref2Str(p->namev)
			);
			return;
		}
		if(!IsStaticModifier(p->modifier)) {
			AddOpcodeBuf(env->Bytecode, OP_THIS);
		}
		GenerateILFactor(self->right, env, cctx);
		GeneratePutProperty(env->Bytecode, p, temp);
		assert(!IsStaticModifier(p->modifier));
	}
}