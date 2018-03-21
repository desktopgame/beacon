#include "il_factor_interface.h"
#include "il_factor_impl.h"
#include "../util/text.h"
#include "../util/logger.h"
#include "../vm/enviroment.h"
#include "../env/type_interface.h"
#include "../util/mem.h"
#include <stdio.h>
#include <assert.h>

void il_factor_dump(il_factor * self, int depth) {
	il_print_layout_form(self->lineno);
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
		case ilfactor_cast:
			il_factor_cast_dump(self->u.cast_, depth);
			break;
		case ilfactor_bool:
			il_factor_bool_dump(self->u.bool_, depth);
			break;
		case ilfactor_null:
			il_factor_null_dump(NULL, depth);
			break;
		case ilfactor_as:
			il_factor_as_dump(self->u.as_, depth);
			break;
		case ilfactor_inc:
			il_factor_inc_dump(self->u.inc_, depth);
			break;
		case ilfactor_dec:
			il_factor_dec_dump(self->u.dec_, depth);
			break;
		default:
			ERROR("ファクターをダンプ出来ませんでした");
			break;
	}
}

void il_factor_generate(il_factor * self, enviroment* env, il_load_cache* cache) {
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_generate(self->u.int_, env, cache);
			break;
		case ilfactor_double:
			il_factor_double_generate(self->u.double_, env, cache);
			break;
		case ilfactor_cquote:
			il_factor_char_generate(self->u.char_, env, cache);
			break;
		case ilfactor_squote:
			il_factor_string_generate(self->u.string_, env, cache);
			break;
		case ilfactor_call:
			il_factor_call_generate(self->u.call_, env, cache);
			break;
		case ilfactor_invoke:
			il_factor_invoke_generate(self->u.invoke_, env, cache);
			break;
		case ilfactor_named_invoke:
			il_factor_named_invoke_generate(self->u.named_invoke_, env, cache);
			break;
		case ilfactor_variable:
			il_factor_variable_generate(self->u.variable_, env, cache);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_generate(self->u.unary_, env, cache);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_generate(self->u.binary_, env, cache);
			break;
		case ilfactor_this:
			il_factor_this_generate(self->u.this_, env, cache);
			break;
		case ilfactor_super:
			il_factor_super_generate(self->u.super_, env, cache);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_generate(self->u.new_instance_, env, cache);
			break;
		case ilfactor_field_access:
			il_factor_field_access_generate(self->u.field_access_, env, cache);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_generate(self->u.static_field_access, env, cache);
			break;
		case ilfactor_cast:
			il_factor_cast_generate(self->u.cast_, env, cache);
			break;
		case ilfactor_bool:
			il_factor_bool_generate(self->u.bool_, env, cache);
			break;
		case ilfactor_null:
			il_factor_null_generate(NULL, env, cache);
			break;
		case ilfactor_as:
			il_factor_as_generate(self->u.as_, env, cache);
			break;
		case ilfactor_inc:
			il_factor_inc_generate(self->u.inc_, env, cache);
			break;
		case ilfactor_dec:
			il_factor_dec_generate(self->u.dec_, env, cache);
			break;
		case ilfactor_op_call:
			il_factor_op_call_generate(self->u.op_call_, env, cache);
			break;
		case ilfactor_name_reference:
			il_factor_name_reference_generate(self->u.name_reference_, env, cache);
			break;
		default:
			ERROR("ファクターを生成出来ませんでした");
			break;
	}
	enviroment_add_range(env, self->lineno);
}

void il_factor_load(il_factor * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
	switch (self->type) {
		case ilfactor_int:
			il_factor_int_load(self->u.int_, env, cache, eh);
			break;
		case ilfactor_double:
			il_factor_double_load(self->u.double_, env, cache, eh);
			break;
		case ilfactor_cquote:
			il_factor_char_load(self->u.char_, env, cache, eh);
			break;
		case ilfactor_squote:
			il_factor_string_load(self->u.string_, env, cache, eh);
			break;
		case ilfactor_call:
			il_factor_call_load(self->u.call_, env, cache, eh);
			break;
		case ilfactor_invoke:
			il_factor_invoke_load(self->u.invoke_, env, cache, eh);
			break;
		case ilfactor_named_invoke:
			il_factor_named_invoke_load(self->u.named_invoke_, env, cache, eh);
			break;
		case ilfactor_variable:
			il_factor_variable_load(self->u.variable_, env, cache, eh);
			break;
		case ilfactor_unary_op:
			il_factor_unary_op_load(self->u.unary_, env, cache, eh);
			break;
		case ilfactor_binary_op:
			il_factor_binary_op_load(self->u.binary_, env, cache, eh);
			break;
		case ilfactor_this:
			il_factor_this_load(self->u.this_, env, cache, eh);
			break;
		case ilfactor_super:
			il_factor_super_load(self->u.super_, env, cache, eh);
			break;
		case ilfactor_new_instance:
			il_factor_new_instance_load(self->u.new_instance_, env, cache, eh);
			break;
		case ilfactor_field_access:
			il_factor_field_access_load(self->u.field_access_, env, cache, eh);
			break;
		case ilfactor_static_field_access:
			il_factor_static_field_access_load(self->u.static_field_access, env, cache, eh);
			break;
		case ilfactor_cast:
			il_factor_cast_load(self->u.cast_, env, cache, eh);
			break;
		case ilfactor_bool:
			//il_factor_bool_load(self->u.bool_, depth);
			break;
		case ilfactor_null:
			il_factor_null_load(NULL, env, cache, eh);
			break;
		case ilfactor_as:
			il_factor_as_load(self->u.as_, env, cache, eh);
			break;
		case ilfactor_inc:
			il_factor_inc_load(self->u.inc_, env, cache, eh);
			break;
		case ilfactor_dec:
			il_factor_dec_load(self->u.dec_, env, cache, eh);
			break;
		case ilfactor_name_reference:
			il_factor_name_reference_load(self->u.name_reference_, env, cache, eh);
			break;
		default:
			ERROR("ファクターの型を取得出来ませんでした");
			break;
	}
}

generic_type* il_factor_eval(il_factor * self, enviroment * env, il_load_cache* cache) {
	generic_type* ret = NULL;
	switch (self->type) {
		case ilfactor_int:
			ret = il_factor_int_eval(self->u.int_, env, cache);
			break;
		case ilfactor_double:
			ret = il_factor_double_eval(self->u.double_, env, cache);
			break;
		case ilfactor_cquote:
			ret = il_factor_char_eval(self->u.char_, env, cache);
			break;
		case ilfactor_squote:
			ret = il_factor_string_eval(self->u.string_, env, cache);
			break;
		case ilfactor_call:
			ret = il_factor_call_eval(self->u.call_, env, cache);
			break;
		case ilfactor_invoke:
			ret = il_factor_invoke_eval(self->u.invoke_, env, cache);
			break;
		case ilfactor_named_invoke:
			ret = il_factor_named_invoke_eval(self->u.named_invoke_, env, cache);
			break;
		case ilfactor_variable:
			ret = il_factor_variable_eval(self->u.variable_, env, cache);
			break;
		case ilfactor_unary_op:
			ret = il_factor_unary_op_eval(self->u.unary_, env, cache);
			break;
		case ilfactor_binary_op:
			ret = il_factor_binary_op_eval(self->u.binary_, env, cache);
			break;
		case ilfactor_this:
			ret = il_factor_this_eval(self->u.this_, env, cache);
			break;
		case ilfactor_super:
			ret = il_factor_super_eval(self->u.super_, env, cache);
			break;
		case ilfactor_new_instance:
			ret = il_factor_new_instance_eval(self->u.new_instance_, env, cache);
			break;
		case ilfactor_field_access:
			ret = il_factor_field_access_eval(self->u.field_access_, env, cache);
			break;
		case ilfactor_static_field_access:
			ret = il_factor_static_field_access_eval(self->u.static_field_access, env, cache);
			break;
		case ilfactor_cast:
			ret = il_factor_cast_eval(self->u.cast_, env, cache);
			break;
		case ilfactor_bool:
			ret = il_factor_bool_eval(self->u.bool_,env, cache);
			break;
		case ilfactor_null:
			ret = il_factor_null_eval(NULL, env, cache);
			break;
		case ilfactor_as:
			ret = il_factor_as_eval(self->u.as_, env, cache);
			break;
		case ilfactor_inc:
			ret = il_factor_inc_eval(self->u.inc_, env, cache);
			break;
		case ilfactor_dec:
			ret = il_factor_dec_eval(self->u.dec_, env, cache);
			break;
		case ilfactor_op_call:
			ret = il_factor_op_call_eval(self->u.op_call_, env, cache);
			break;
		case ilfactor_name_reference:
			ret = il_factor_name_reference_eval(self->u.name_reference_, env, cache);
			break;
		default:
			ERROR("ファクターの型を取得出来ませんでした");
			break;
	}
	assert(ret != NULL);
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
		case ilfactor_cast:
			il_factor_cast_delete(self->u.cast_);
			break;
		case ilfactor_bool:
			il_factor_bool_delete(self->u.bool_);
			break;
		case ilfactor_null:
			break;
		case ilfactor_as:
			il_factor_as_delete(self->u.as_);
			break;
		case ilfactor_inc:
			il_factor_inc_delete(self->u.inc_);
			break;
		case ilfactor_dec:
			il_factor_dec_delete(self->u.dec_);
			break;
		case ilfactor_name_reference:
			il_factor_name_reference_delete(self->u.name_reference_);
			break;
		default:
			ERROR("ファクターを開放出来ませんでした");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
