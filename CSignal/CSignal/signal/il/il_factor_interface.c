#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "../util/text.h"
#include "../util/logger.h"
#include "../vm/enviroment.h"
#include <stdio.h>

void il_factor_dump(il_factor * self, int depth) {
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_dump(self->u.int_, depth);
			break;
		case ilfactor_double:
			il_factor_double_dump(self->u.double_, depth);
			break;
		case ilfactor_cquote:
			il_factor_char_dump(self->u.char_, depth);
			break;
		case ilfactor_squote:
			il_factor_string_dump(self->u.string_, depth);
			break;
		case ilfactor_call:
			il_factor_call_dump(self->u.call_, depth);
			break;
		case ilfactor_invoke:
			il_factor_invoke_dump(self->u.invoke_, depth);
			break;
		case ilfactor_variable:
			il_factor_variable_dump(self->u.variable_, depth);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_dump(self->u.unary_, depth);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_dump(self->u.binary_, depth);
			break;
		default:
			ERROR("ファクターをダンプ出来ませんでした");
			break;
	}
}

void il_factor_generate(il_factor * self, enviroment* env) {
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_generate(self->u.int_, env);
			break;
		case ilfactor_double:
			il_factor_double_generate(self->u.double_, env);
			break;
		case ilfactor_cquote:
			il_factor_char_generate(self->u.char_, env);
			break;
		case ilfactor_squote:
			il_factor_string_generate(self->u.string_, env);
			break;
		case ilfactor_call:
			il_factor_call_generate(self->u.call_, env);
			break;
		case ilfactor_invoke:
			il_factor_invoke_generate(self->u.int_, env);
			break;
		case ilfactor_variable:
			il_factor_variable_generate(self->u.variable_, env);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_generate(self->u.unary_, env);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_generate(self->u.binary_, env);
			break;
		default:
			ERROR("ファクターを生成出来ませんでした");
			break;
	}
}

void il_factor_delete(il_factor * self) {
	if (self == NULL) {
		return;
	}
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_delete(self->u.int_);
			break;
		case ilfactor_double:
			il_factor_double_delete(self->u.double_);
			break;
		case ilfactor_cquote:
			il_factor_char_delete(self->u.char_);
			break;
		case ilfactor_squote:
			il_factor_string_delete(self->u.string_);
			break;
		case ilfactor_call:
			il_factor_call_delete(self->u.call_);
			break;
		case ilfactor_invoke:
			il_factor_invoke_delete(self->u.invoke_);
			break;
		case ilfactor_variable:
			il_factor_variable_delete(self->u.variable_);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_delete(self->u.unary_);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_delete(self->u.binary_);
			break;
		default:
			ERROR("ファクターを開放出来ませんでした");
			break;
	}
	free(self);
}
