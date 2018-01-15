#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "../util/text.h"
#include "../util/logger.h"
#include "../vm/enviroment.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
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
		case ilfactor_named_invoke:
			il_factor_named_invoke_dump(self->u.named_invoke_, depth);
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
		case ilfactor_this:
			il_factor_this_dump(self->u.this_, depth);
			break;
		case ilfactor_super:
			il_factor_super_dump(self->u.super_, depth);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_dump(self->u.new_instance_, depth);
			break;
		case ilfactor_field_access:
			il_factor_field_access_dump(self->u.field_access_, depth);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_dump(self->u.static_field_access, depth);
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
			il_factor_invoke_generate(self->u.invoke_, env);
			break;
		case ilfactor_named_invoke:
			il_factor_named_invoke_generate(self->u.named_invoke_, env);
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
		case ilfactor_this:
			il_factor_this_generate(self->u.this_, env);
			break;
		case ilfactor_super:
			il_factor_super_generate(self->u.super_, env);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_generate(self->u.new_instance_, env);
			break;
		case ilfactor_field_access:
			il_factor_field_access_generate(self->u.field_access_, env);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_generate(self->u.static_field_access, env);
			break;
		default:
			ERROR("ファクターを生成出来ませんでした");
			break;
	}
}

void il_factor_load(il_factor * self, enviroment * env, il_ehandler * eh) {
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_load(self->u.int_, env, eh);
			break;
		case ilfactor_double:
			il_factor_double_load(self->u.double_, env, eh);
			break;
		case ilfactor_cquote:
			il_factor_char_load(self->u.char_, env, eh);
			break;
		case ilfactor_squote:
			il_factor_string_load(self->u.string_, env, eh);
			break;
		case ilfactor_call:
			il_factor_call_load(self->u.call_, env, eh);
			break;
		case ilfactor_invoke:
			il_factor_invoke_load(self->u.invoke_, env, eh);
			break;
		case ilfactor_named_invoke:
			il_factor_named_invoke_load(self->u.named_invoke_, env, eh);
			break;
		case ilfactor_variable:
			il_factor_variable_load(self->u.variable_, env, eh);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_load(self->u.unary_, env, eh);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_load(self->u.binary_, env, eh);
			break;
		case ilfactor_this:
			il_factor_this_load(self->u.this_, env, eh);
			break;
		case ilfactor_super:
			il_factor_super_load(self->u.super_, env, eh);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_load(self->u.new_instance_, env, eh);
			break;
		case ilfactor_field_access:
			il_factor_field_access_load(self->u.field_access_, env, eh);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_load(self->u.static_field_access, env, eh);
			break;
		default:
			ERROR("ファクターの型を取得出来ませんでした");
			break;
	}
}

type * il_factor_eval(il_factor * self, enviroment * env) {
	type* ret = NULL;
	switch (self->type) {
		case ilfactor_int:
			ret = il_factor_int_eval(self->u.int_, env);
			break;
		case ilfactor_double:
			ret = il_factor_double_eval(self->u.double_, env);
			break;
		case ilfactor_cquote:
			ret = il_factor_char_eval(self->u.char_, env);
			break;
		case ilfactor_squote:
			ret = il_factor_string_eval(self->u.string_, env);
			break;
		case ilfactor_call:
			ret = il_factor_call_eval(self->u.call_, env);
			break;
		case ilfactor_invoke:
			ret = il_factor_invoke_eval(self->u.invoke_, env);
			break;
		case ilfactor_named_invoke:
			ret = il_factor_named_invoke_eval(self->u.named_invoke_, env);
			break;
		case ilfactor_variable:
			ret = il_factor_variable_eval(self->u.variable_, env);
			break;
		case ilfactor_unary_op:
			ret = il_factor_unary_op_eval(self->u.unary_, env);
			break;
		case ilfactor_binary_op:
			ret = il_factor_binary_op_eval(self->u.binary_, env);
			break;
		case ilfactor_this:
			ret = il_factor_this_eval(self->u.this_, env);
			break;
		case ilfactor_super:
			ret = il_factor_super_eval(self->u.super_, env);
			break;
		case ilfactor_new_instance:
			ret = il_factor_new_instance_eval(self->u.new_instance_, env);
			break;
		case ilfactor_field_access:
			ret = il_factor_field_access_eval(self->u.field_access_, env);
			break;
		case ilfactor_static_field_access:
			ret = il_factor_static_field_access_eval(self->u.static_field_access, env);
			break;
		default:
			ERROR("ファクターの型を取得出来ませんでした");
			break;
	}
	return ret;
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
		case ilfactor_named_invoke:
			il_factor_named_invoke_delete(self->u.named_invoke_);
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
		case ilfactor_this:
			il_factor_this_delete(self->u.this_);
			break;
		case ilfactor_super:
			il_factor_super_delete(self->u.super_);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_delete(self->u.new_instance_);
			break;
		case ilfactor_field_access:
			il_factor_field_access_delete(self->u.field_access_);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_delete(self->u.static_field_access);
			break;
		default:
			ERROR("ファクターを開放出来ませんでした");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
