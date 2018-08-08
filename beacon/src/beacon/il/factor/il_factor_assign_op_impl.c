#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include "../../env/property.h"
#include "../../env/property_body.h"
#include "../../vm/symbol_entry.h"
#include "../../env/field.h"

static void assign_by_namebase(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_to_field(il_factor_assign_op* self,il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx);
static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void check_final(il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx);
static bool can_assign_to_field(field* f, il_factor_assign_op* self, enviroment* env, call_context* cctx);

il_factor* il_factor_wrap_assign(il_factor_assign_op* self) {
	il_factor* ret = il_factor_new(ilfactor_assign_op);
	ret->u.assign_ = self;
	return ret;
}

il_factor_assign_op* il_factor_assign_op_new() {
	il_factor_assign_op* ret = (il_factor_assign_op*)MEM_MALLOC(sizeof(il_factor_assign_op));
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void il_factor_assign_op_dump(il_factor_assign_op* self, int depth) {
	text_putindent(depth);
	text_printfln("assign");
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_assign_op_load(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_load(self->left, env, cctx);
	il_factor_load(self->right, env, cctx);
}

void il_factor_assign_op_generate(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	if(self->left->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(self->left);
		symbol_entry* e = symbol_table_entry(env->sym_table, NULL, ilvar->fqcn->namev);
		il_factor_generate(self->right, env, cctx);
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, e->index);
		//NOTE:constかどうかの検査
	//foo.bar = xxx
	} else if(self->left->type == ilfactor_member_op) {
		il_factor_member_op* ilmem = IL_FACT2MEM(self->left);
		il_factor* ilsrc = ilmem->fact;
		if(ilsrc->type == ilfactor_variable) {
			assign_by_namebase(self, env, cctx);
		//インスタンスフィールドへの代入
		} else {
			assign_to_field(self, ilmem->fact, self->right, ilmem->namev, env, cctx);
		}
	} else if(self->left->type == ilfactor_property) {
		assign_to_property(self, env, cctx);
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
	il_factor_member_op* ilmem = IL_FACT2MEM(self->left);
	il_factor* ilsrc = ilmem->fact;
	il_factor_variable* ilvar = IL_FACT2VAR(ilsrc);
	//staticなフィールドへの代入
	if(ilvar->type == ilvariable_type_static) {
		class_* cls = TYPE2CLASS(call_context_eval_type(cctx, ilvar->u.static_->fqcn));
		int temp = -1;
		field* sf = class_find_sfield(cls, ilmem->namev, &temp);
		assert(temp != -1);
		il_factor_generate(self->right, env, cctx);
		opcode_buf_add(env->buf, (vector_item)op_put_static);
		opcode_buf_add(env->buf, (vector_item)cls->parent->absolute_index);
		opcode_buf_add(env->buf, (vector_item)temp);
		//指定の静的フィールドにアクセスできない
		if(!class_accessible_field(call_context_class(cctx), sf)) {
			bc_error_throw(bcerror_can_t_access_field,
				string_pool_ref2str(type_name(cls->parent)),
				string_pool_ref2str(sf->namev)
			);
			return;
		}
		//finalなので書き込めない
		if(modifier_is_final(sf->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field,
				string_pool_ref2str(type_name(cls->parent)),
				string_pool_ref2str(sf->namev)
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
	opcode_buf_add(env->buf, (vector_item)op_put_field);
	opcode_buf_add(env->buf, (vector_item)temp);
	//型の互換性を検査
	if(!can_assign_to_field(f, self, env, cctx)) {
		return;
	}
	//指定のインスタンスフィールドにアクセスできない
	if(!class_accessible_field(call_context_class(cctx), f)) {
		bc_error_throw(bcerror_can_t_access_field,
			string_pool_ref2str(type_name(cls->parent)),
			string_pool_ref2str(f->namev)
		);
	}
	check_final(receiver, source, namev, env, cctx);
}

static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_property* prop = self->left->u.prop;
	property* pp = prop->p;
	bool is_static = modifier_is_static(prop->p->modifier);
	//プロパティへアクセスできない
	if(!class_accessible_property(call_context_class(cctx), pp)) {
		bc_error_throw(bcerror_can_t_access_field,
			string_pool_ref2str(type_name(pp->parent)),
			string_pool_ref2str(pp->namev)
		);
		return;
	}
	if(!class_accessible_property_accessor(call_context_class(cctx), pp->set)) {
		bc_error_throw(bcerror_can_t_access_field,
			string_pool_ref2str(type_name(pp->parent)),
			string_pool_ref2str(pp->namev)
		);
		return;
	}
	if(generic_type_distance(prop->p->gtype, il_factor_eval(self->right, env, cctx)) < 0) {
		bc_error_throw(bcerror_assign_not_compatible_property,
			string_pool_ref2str(type_name(prop->p->parent)),
			string_pool_ref2str(prop->p->namev)
		);
		return;
	}
	if(prop->p->is_short) {
		if(is_static) {
			il_factor_generate(self->right, env, cctx);
			opcode_buf_add(env->buf, (vector_item)op_put_static);
			opcode_buf_add(env->buf, (vector_item)prop->p->parent->absolute_index);
			opcode_buf_add(env->buf, (vector_item)class_get_field_by_property(TYPE2CLASS(prop->p->parent), prop->p));
		} else {
			il_factor_generate(prop->fact, env, cctx);
			il_factor_generate(self->right, env, cctx);
			opcode_buf_add(env->buf, (vector_item)op_put_field);
			opcode_buf_add(env->buf, (vector_item)class_get_field_by_property(TYPE2CLASS(prop->p->parent), prop->p));
		}
	} else {
		if(is_static) {
			il_factor_generate(self->right, env, cctx);
			opcode_buf_add(env->buf, (vector_item)op_put_static_property);
			opcode_buf_add(env->buf, (vector_item)prop->p->parent->absolute_index);
			opcode_buf_add(env->buf, (vector_item)prop->index);
		} else {
			il_factor_generate(prop->fact, env, cctx);
			il_factor_generate(self->right, env, cctx);
			opcode_buf_add(env->buf, (vector_item)op_put_property);
			opcode_buf_add(env->buf, (vector_item)prop->index);
		}
	}
}

static bool can_assign_to_field(field* f, il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(self->right, env, cctx);
	int dist = generic_type_distance(f->gtype, gt);
	if(dist >= 0) {
		return true;
	} else {
		bc_error_throw(bcerror_assign_not_compatible_field,
			string_pool_ref2str(type_name(f->parent)),
			string_pool_ref2str(f->namev)
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
		if(modifier_is_final(f->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field,
				string_pool_ref2str(type_name(cls->parent)),
				string_pool_ref2str(f->namev)
			);
		}
	} else {
		//コンストラクタであっても static final の場合は書き込めない
		if(modifier_is_final(f->modifier) &&
		   modifier_is_static(f->modifier)) {
			bc_error_throw(bcerror_assign_to_final_field,
				string_pool_ref2str(type_name(cls->parent)),
				string_pool_ref2str(f->namev)
			);
		}
		f->not_initialized_at_ctor = true;
	}
}