#include "il_factor_excor_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"
#include "../../../env/operator_overload.h"

il_factor_excor_op* il_factor_excor_op_new(operator_type type) {
	il_factor_excor_op* ret = (il_factor_excor_op*)MEM_MALLOC(sizeof(il_factor_excor_op));
	ret->type = type;
	ret->parent = NULL;
	return ret;
}

void il_factor_excor_op_dump(il_factor_excor_op* self, int depth) {
	text_putindent(depth);
	operator_fprintf(self->type, stdout);
	text_putline();
}

generic_type* il_factor_excor_op_eval(il_factor_excor_op * self, enviroment * env) {
	generic_type* lgtype = il_factor_eval(self->parent->left, env);
	generic_type* rgtype = il_factor_eval(self->parent->right, env);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	if(il_factor_binary_op_int_int(self->parent, env)) {
		return TYPE2GENERIC(TYPE_INT);
	}
	if(il_factor_binary_op_bool_bool(self->parent, env)) {
		return TYPE2GENERIC(TYPE_BOOL);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	assert(self->operator_index != -1);
	operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
	return operator_ov->return_gtype;
}

void il_factor_excor_op_generate(il_factor_excor_op* self, enviroment* env) {
	//演算子オーバーロードが見つからない
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env);
		il_factor_generate(self->parent->left, env);
		if(il_factor_binary_op_int_int(self->parent, env)) {
			opcode_buf_add(env->buf, op_iexcor);
		} else if(il_factor_binary_op_bool_bool(self->parent, env)) {
			opcode_buf_add(env->buf, op_bexcor);
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env);
		il_factor_generate(self->parent->left, env);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_excor_op_load(il_factor_excor_op* self, enviroment* env) {
	if(!il_factor_binary_op_int_int(self->parent, env) &&
	   !il_factor_binary_op_bool_bool(self->parent, env)) {
	self->operator_index = il_factor_binary_op_index(self->parent, env);
	}
}

void il_factor_excor_op_delete(il_factor_excor_op* self) {
	MEM_FREE(self);
}

char* il_factor_excor_op_tostr(il_factor_excor_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}