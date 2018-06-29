#include "il_factor_assign_op_impl.h"
#include "../il_factor_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_impl.h"
#include "../../vm/symbol_entry.h"

il_factor* il_factor_wrap_assign(il_factor_assign_op* self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_assign_op;
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

void il_factor_assign_op_load(il_factor_assign_op* self, enviroment* env) {
	il_factor_load(self->left, env);
	il_factor_load(self->right, env);
}

void il_factor_assign_op_generate(il_factor_assign_op* self, enviroment* env) {
	if(self->left->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(self->left);
		symbol_entry* e = symbol_table_entry(env->sym_table, NULL, ilvar->fqcn->name);
		il_factor_generate(self->right, env);
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, e->index);
	} else if(self->left->type == ilfactor_member_op) {
		il_factor_member_op* ilmem = IL_FACT2MEM(self->left);
		il_factor* ilsrc = ilmem->fact;
		if(ilsrc->type == ilfactor_variable) {
			il_factor_variable* ilvar = IL_FACT2VAR(ilsrc);
			//staticなフィールドへの代入
			if(ilvar->type == ilvariable_type_static) {
				class_* cls = cc_class(ilvar->u.static_->fqcn);
				int temp = -1;
				class_find_sfield(cls, ilmem->name, &temp);
				assert(temp != -1);
				il_factor_generate(self->right, env);
				opcode_buf_add(env->buf, (vector_item)op_put_static);
				opcode_buf_add(env->buf, (vector_item)cls->parent->absolute_index);
				opcode_buf_add(env->buf, (vector_item)temp);
			} else goto inst;
			//インスタンスフィールドへの代入
			} else {
			inst: {
				generic_type* gt = il_factor_eval(ilmem->fact, env);
				class_* cls = TYPE2CLASS(gt->core_type);
				int temp = -1;
				class_find_field(cls, ilmem->name, &temp);
				assert(temp != -1);
				il_factor_generate(ilmem->fact, env);
				il_factor_generate(self->right, env);
				opcode_buf_add(env->buf, (vector_item)op_put_field);
				opcode_buf_add(env->buf, (vector_item)temp);
			}
		}
	}
}

generic_type* il_factor_assign_op_eval(il_factor_assign_op* self, enviroment* env) {
	return il_factor_eval(self->right, env);
}

void il_factor_assign_op_delete(il_factor_assign_op* self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}