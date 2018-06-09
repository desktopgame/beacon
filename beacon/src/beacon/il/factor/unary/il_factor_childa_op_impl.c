#include "il_factor_childa_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

il_factor_childa_op* il_factor_childa_op_new(operator_type type) {
	il_factor_childa_op* ret = (il_factor_childa_op*)MEM_MALLOC(sizeof(il_factor_childa_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_childa_op_dump(il_factor_childa_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_childa_op_eval(il_factor_childa_op * self, enviroment * env) {
	generic_type* gtype = il_factor_eval(self->parent->a, env);
	if(self->operator_index == -1) {
		//il_factor_generate(self->parent->a, env);
		if(GENERIC2TYPE(gtype) == TYPE_INT) {
			return TYPE2GENERIC(TYPE_INT);
		} else if(GENERIC2TYPE(gtype) == TYPE_BOOL) {
			return TYPE2GENERIC(TYPE_BOOL);
		} else {
			assert(false);
		}
	} else {
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		assert(self->operator_index != -1);
		operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(gtype)), self->operator_index);
		return operator_ov->return_gtype;
	}
}

void il_factor_childa_op_generate(il_factor_childa_op* self, enviroment* env) {
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->a, env);
		generic_type* gtype = il_factor_eval(self->parent->a, env);
		if(GENERIC2TYPE(gtype) == TYPE_INT) {
			opcode_buf_add(env->buf, op_iflip);
		} else if(GENERIC2TYPE(gtype) == TYPE_BOOL) {
			opcode_buf_add(env->buf, op_bflip);
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->a, env);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_childa_op_load(il_factor_childa_op* self, enviroment* env) {
	self->operator_index = il_factor_unary_op_index(self->parent, env);
}

void il_factor_childa_op_delete(il_factor_childa_op* self) {
	MEM_FREE(self);
}

char* il_factor_childa_op_tostr(il_factor_childa_op* self, enviroment* env) {
	return il_factor_unary_op_tostr_simple(self->parent, env);
}