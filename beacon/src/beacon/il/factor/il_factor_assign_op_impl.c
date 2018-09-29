#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include "../../env/property.h"
#include "../../env/property_body.h"
#include "../../vm/symbol_entry.h"
#include "../../vm/generate.h"
#include "../../il/il_argument.h"
#include "../../env/field.h"

static void assign_by_namebase(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_to_field(il_factor_assign_op* self,il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx);
static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_to_array(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_by_call(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_by_invoke(il_factor_invoke* lhs, il_factor* rhs, enviroment* env, call_context* cctx);
static void assign_by_invoke_bound(il_factor_invoke_bound* lhs, il_factor* rhs, enviroment* env, call_context* cctx);
static void check_final(il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx);
static bool can_assign_to_field(field* f, il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void generate_assign_to_variable(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void generate_assign_to_variable_local(il_factor_assign_op* self, enviroment* env, call_context* cctx);

il_factor* il_factor_wrap_assign(il_factor_assign_op* self) {
	il_factor* ret = il_factor_new(ilfactor_assign_T);
	ret->u.assign_ = self;
	return ret;
}

il_factor_assign_op* il_factor_assign_op_new() {
	il_factor_assign_op* ret = (il_factor_assign_op*)MEM_MALLOC(sizeof(il_factor_assign_op));
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void il_factor_assign_op_load(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->left, env, cctx);
	il_factor_load(self->right, env, cctx);
	//voidは代入できない
	generic_type* gret = il_factor_eval(self->right, env, cctx);
	BC_ERROR();
	if(gret->core_type != NULL &&
	   gret->core_type == TYPE_VOID) {
		   bc_error_throw(bcerror_void_assign_T);
		return;
	}
}

void il_factor_assign_op_generate(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	if(self->left->type == ilfactor_variable_T) {
		generate_assign_to_variable(self, env, cctx);
		//NOTE:constかどうかの検査
	//foo.bar = xxx
	} else if(self->left->type == ilfactor_member_op_T) {
		il_factor_member_op* ilmem = self->left->u.member_;
		il_factor* ilsrc = ilmem->fact;
		if(ilsrc->type == ilfactor_variable_T) {
			assign_by_namebase(self, env, cctx);
		//インスタンスフィールドへの代入
		} else {
			assign_to_field(self, ilmem->fact, self->right, ilmem->namev, env, cctx);
		}
	} else if(self->left->type == ilfactor_property_T) {
		assign_to_property(self, env, cctx);
	} else if(self->left->type == ilfactor_subscript_T) {
		assign_to_array(self, env, cctx);
	} else if(self->left->type == ilfactor_call_op_T) {
		assign_by_call(self, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* il_factor_assign_op_eval(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	return il_factor_eval(self->right, env, cctx);
}

void il_factor_assign_op_delete(il_factor_assign_op* self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}
//private
static void assign_by_namebase(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_member_op* ilmem = self->left->u.member_;
	il_factor* ilsrc = ilmem->fact;
	il_factor_variable* ilvar = ilsrc->u.variable_;
	//staticなフィールドへの代入
	if(ilvar->type == ilvariable_type_static_T) {
		class_* cls = TYPE2CLASS(call_context_eval_type(cctx, ilvar->u.static_->fqcn));
		int temp = -1;
		field* sf = class_find_sfield(cls, ilmem->namev, &temp);
		assert(temp != -1);
		il_factor_generate(self->right, env, cctx);
		generate_put_field(env->buf, sf, temp);
		//指定の静的フィールドにアクセスできない
		if(!class_accessible_field(call_context_class(cctx), sf)) {
			bc_error_throw(bcerror_can_t_access_field_T,
				Ref2Str(type_name(cls->parent)),
				Ref2Str(sf->namev)
			);
			return;
		}
		//finalなので書き込めない
		if(IsFinalModifier(sf->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field_T,
				Ref2Str(type_name(cls->parent)),
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

static void assign_to_field(il_factor_assign_op* self, il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->core_type);
	int temp = -1;
	field* f = class_find_field_tree(cls, namev, &temp);
	assert(temp != -1);
	il_factor_generate(receiver, env, cctx);
	il_factor_generate(source, env, cctx);
	generate_put_field(env->buf, f, temp);
	//型の互換性を検査
	if(!can_assign_to_field(f, self, env, cctx)) {
		return;
	}
	//指定のインスタンスフィールドにアクセスできない
	if(!class_accessible_field(call_context_class(cctx), f)) {
		bc_error_throw(bcerror_can_t_access_field_T,
			Ref2Str(type_name(cls->parent)),
			Ref2Str(f->namev)
		);
	}
	check_final(receiver, source, namev, env, cctx);
}

static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_property* prop = self->left->u.prop;
	property* pp = prop->p;
	bool is_static = IsStaticModifier(prop->p->modifier);
	BC_ERROR();
	//プロパティへアクセスできない
	if(!class_accessible_property(call_context_class(cctx), pp)) {
		bc_error_throw(bcerror_can_t_access_field_T,
			Ref2Str(type_name(pp->parent)),
			Ref2Str(pp->namev)
		);
		return;
	}
	if(!class_accessible_property_accessor(call_context_class(cctx), pp->set)) {
		bc_error_throw(bcerror_can_t_access_field_T,
			Ref2Str(type_name(pp->parent)),
			Ref2Str(pp->namev)
		);
		return;
	}
	if(generic_type_distance(prop->p->gtype, il_factor_eval(self->right, env, cctx), cctx) < 0) {
		bc_error_throw(bcerror_assign_not_compatible_property_T,
			Ref2Str(type_name(prop->p->parent)),
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
		il_factor_generate(prop->fact, env, cctx);
	}
	il_factor_generate(self->right, env, cctx);
	generate_put_property(env->buf, pp, prop->index);
}

static void assign_to_array(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_subscript* subs = self->left->u.subscript;
	il_factor_generate(subs->receiver, env, cctx);
	il_factor_generate(subs->pos, env, cctx);
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, subs->operator_index);
}

static void assign_by_call(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_call_op* call = self->left->u.call_;
	if(call->type == ilcall_type_invoke_static_T) {
		bc_error_throw(
			bcerror_lhs_is_not_subscript_T,
			Ref2Str(call->u.invoke_static_->namev)
		);
		return;
	}
	if(call->type == ilcall_type_invoke_T) {
		assign_by_invoke(call->u.invoke_, self->right, env, cctx);
	} else if(call->type == ilcall_type_invoke_bound_T) {
		assign_by_invoke_bound(call->u.invoke_bound_, self->right, env, cctx);
	} else {
		assert(false);
	}
}

static void assign_by_invoke(il_factor_invoke* lhs, il_factor* rhs, enviroment* env, call_context* cctx) {
	int temp = -1;
	if(lhs->tag != instance_invoke_subscript_T) {
		bc_error_throw(bcerror_assign_to_invoke_T,
			Ref2Str(lhs->namev)
		);
		return;
	}
	il_factor_invoke_find_set(lhs, rhs, env, cctx, &temp);
	for(int i=0; i<lhs->args->length; i++) {
		il_argument* arg = AtVector(lhs->args, i);
		il_factor_generate(arg->factor, env, cctx);
	}
	il_factor_generate(rhs, env, cctx);
	il_factor_generate(lhs->receiver, env, cctx);
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, temp);
	opcode_buf_add(env->buf, op_nop);
}

static void assign_by_invoke_bound(il_factor_invoke_bound* lhs, il_factor* rhs, enviroment* env, call_context* cctx) {
	int temp = -1;
	il_factor_invoke_bound_find_set(lhs, rhs, env, cctx, &temp);
	assert(lhs->args->length == 1);
	for(int i=0; i<lhs->args->length; i++) {
		il_argument* arg = AtVector(lhs->args, i);
		il_factor_generate(arg->factor, env, cctx);
	}
	il_factor_generate(rhs, env, cctx);
	//il_factor_generate(lhs->receiver, env, cctx);
	subscript_descriptor subs = lhs->u.subscript;
	if(subs.tag == subscript_local_T) {
		opcode_buf_add(env->buf, op_load);
		opcode_buf_add(env->buf, subs.index);
	} else if(subs.tag == subscript_field_T) {
		opcode_buf_add(env->buf, op_this);
		generate_get_field(env->buf, subs.u.fi, subs.index);
	} else if(subs.tag == subscript_property_T) {
		opcode_buf_add(env->buf, op_this);
		generate_get_property(env->buf, subs.u.prop, subs.index);
	}
	opcode_buf_add(env->buf, op_invokeoperator);
	opcode_buf_add(env->buf, temp);
}

static bool can_assign_to_field(field* f, il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(self->right, env, cctx);
	int dist = generic_type_distance(f->gtype, gt, cctx);
	if(dist >= 0) {
		return true;
	} else {
		bc_error_throw(bcerror_assign_not_compatible_field_T,
			Ref2Str(type_name(f->parent)),
			Ref2Str(f->namev)
		);
		return false;
	}
}

static void check_final(il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->core_type);
	int temp = -1;
	field* f = class_find_field_tree(cls, namev, &temp);
	assert(temp != -1);
	//コンストラクタ以外の場所では finalフィールドは初期化できない
	if(cctx->tag != call_ctor_T) {
		//finalなので書き込めない
		if(IsFinalModifier(f->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field_T,
				Ref2Str(type_name(cls->parent)),
				Ref2Str(f->namev)
			);
		}
	} else {
		//コンストラクタであっても static final の場合は書き込めない
		if(IsFinalModifier(f->modifier) &&
		   IsStaticModifier(f->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field_T,
				Ref2Str(type_name(cls->parent)),
				Ref2Str(f->namev)
			);
		}
		f->not_initialized_at_ctor = true;
	}

}

static void generate_assign_to_variable(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	assert(self->left->type == ilfactor_variable_T);
	il_factor_variable* ilvar = self->left->u.variable_;
	if(ilvar->type == ilvariable_type_local_T) {
		generate_assign_to_variable_local(self, env, cctx);
	}
}

static void generate_assign_to_variable_local(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_variable* ilvar = self->left->u.variable_;
	il_factor_variable_local* illoc = ilvar->u.local_;
	//src のような名前がローカル変数を示す場合
	if(illoc->type == variable_local_scope_T) {
		#if defined(DEBUG)
		const char* vname = Ref2Str(ilvar->fqcn->namev);
		#endif
		symbol_entry* e = symbol_table_entry(env->sym_table, NULL, ilvar->fqcn->namev);
		//e==NULL の時変数がない
		il_factor_generate(self->right, env, cctx);
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, e->index);
		if(generic_type_distance(e->gtype, il_factor_eval(self->right, env, cctx), cctx) < 0) {
			bc_error_throw(bcerror_assign_not_compatible_local_T,
				Ref2Str(ilvar->fqcn->namev)
			);
			return;
		}
	//src のような名前がフィールドを示す場合
	} else if(illoc->type == variable_local_field_T) {
		int temp = -1;
		field* f = class_find_field_tree(call_context_class(cctx), illoc->namev, &temp);
		if(temp == -1) {
			f = class_find_sfield_tree(call_context_class(cctx), illoc->namev, &temp);
		}
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!IsStaticModifier(f->modifier) &&
		    call_context_is_static(cctx)) {
			bc_error_throw(bcerror_access_to_this_at_static_method_T,
				Ref2Str(type_name(f->parent)),
				Ref2Str(f->namev)
			);
			return;
		}
		if(!IsStaticModifier(f->modifier)) {
			opcode_buf_add(env->buf, op_this);
		}
		il_factor_generate(self->right, env, cctx);
		generate_put_field(env->buf, f, temp);
		//assert(!IsStaticModifier(f->modifier));
	//src のような名前がプロパティを示す場合
	} else if(illoc->type == variable_local_property_T) {
		int temp = -1;
		property* p = class_find_property_tree(call_context_class(cctx), illoc->namev, &temp);
		assert(temp != -1);
		//フィールドはstaticでないが
		//現在のコンテキストはstaticなので this にアクセスできない
		if(!IsStaticModifier(p->modifier) &&
		    call_context_is_static(cctx)) {
			bc_error_throw(bcerror_access_to_this_at_static_method_T,
				Ref2Str(type_name(p->parent)),
				Ref2Str(p->namev)
			);
			return;
		}
		if(!IsStaticModifier(p->modifier)) {
			opcode_buf_add(env->buf, op_this);
		}
		il_factor_generate(self->right, env, cctx);
		generate_put_property(env->buf, p, temp);
		assert(!IsStaticModifier(p->modifier));
	}
}