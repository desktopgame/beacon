#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include "../../vm/symbol_entry.h"

static void assign_by_namebase(il_factor_assign_op* self, enviroment* env, call_context* cctx);
static void assign_to_field(il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx);
static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx);

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
			assign_to_field(ilmem->fact, self->right, ilmem->namev, env, cctx);
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
		class_find_sfield(cls, ilmem->namev, &temp);
		assert(temp != -1);
		il_factor_generate(self->right, env, cctx);
		opcode_buf_add(env->buf, (vector_item)op_put_static);
		opcode_buf_add(env->buf, (vector_item)cls->parent->absolute_index);
		opcode_buf_add(env->buf, (vector_item)temp);
	} else {
		assign_to_field(ilmem->fact, self->right, ilmem->namev, env, cctx);
	}
}

static void assign_to_field(il_factor* receiver, il_factor* source, string_view namev, enviroment* env, call_context* cctx) {
	generic_type* gt = il_factor_eval(receiver, env, cctx);
	class_* cls = TYPE2CLASS(gt->core_type);
	int temp = -1;
	class_find_field_tree(cls, namev, &temp);
	assert(temp != -1);
	il_factor_generate(receiver, env, cctx);
	il_factor_generate(source, env, cctx);
	opcode_buf_add(env->buf, (vector_item)op_put_field);
	opcode_buf_add(env->buf, (vector_item)temp);
}

static void assign_to_property(il_factor_assign_op* self, enviroment* env, call_context* cctx) {
	il_factor_property* prop = self->left->u.prop;
	bool is_static = modifier_is_static(prop->p->modifier);
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