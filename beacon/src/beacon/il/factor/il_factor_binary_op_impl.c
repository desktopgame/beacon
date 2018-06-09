#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include "../il_factor_impl.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../util/mem.h"
#include "binary/il_factor_arithmetic_op_impl.h"
#include "binary/il_factor_compare_op_impl.h"
//#include "binary/il_factor_assign_op_impl.h"
#include "binary/il_factor_logic_op_impl.h"
#include "binary/il_factor_shift_op_impl.h"
#include "binary/il_factor_excor_op_impl.h"

static bool type_test(il_factor_binary_op* self, enviroment* env, type* t);

il_factor * il_factor_wrap_binary(il_factor_binary_op * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_binary_op;
	ret->u.binary_ = self;
	return ret;
}

il_factor_binary_op * il_factor_binary_op_new(operator_type type) {
	il_factor_binary_op* ret = (il_factor_binary_op*)MEM_MALLOC(sizeof(il_factor_binary_op));
	ret->type = type;
	ret->left = NULL;
	ret->right = NULL;
	ret->load = false;
	return ret;
}

void il_factor_binary_op_dump(il_factor_binary_op * self, int depth) {
	switch(self->category) {
		case operator_carithmeric:
			il_factor_arithmetic_op_dump(self->u.arithmetic_op, depth);
			break;
		case operator_ccompare:
			il_factor_compare_op_dump(self->u.compare_op, depth);
			break;
		case operator_clogic:
			il_factor_logic_op_dump(self->u.logic_op, depth);
			break;
		case operator_cshift:
			il_factor_shift_op_dump(self->u.shift_op, depth);
			break;
		case operator_cexcor:
			il_factor_excor_op_dump(self->u.excor_op, depth);
			break;
	}
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env) {
	switch(self->category) {
		case operator_carithmeric:
			il_factor_arithmetic_op_generate(self->u.arithmetic_op, env);
			break;
		case operator_ccompare:
			il_factor_compare_op_generate(self->u.compare_op, env);
			break;
		case operator_clogic:
			il_factor_logic_op_generate(self->u.logic_op, env);
			break;
		case operator_cshift:
			il_factor_shift_op_generate(self->u.shift_op, env);
			break;
		case operator_cexcor:
			il_factor_excor_op_generate(self->u.excor_op, env);
			break;
	}
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env) {
	if(self->load) {
		return;
	}
	self->load = true;
	il_factor_load(self->left, env);
	il_factor_load(self->right, env);
	//カテゴリーわけ
	if(operator_arithmetic(self->type)) {
		self->category = operator_carithmeric;
		il_factor_arithmetic_op* arith = il_factor_arithmetic_op_new(self->type);
		arith->parent = self;
		self->u.arithmetic_op = arith;
		il_factor_arithmetic_op_load(arith, env);
	} else if(operator_compare(self->type)) {
		self->category = operator_ccompare;
		il_factor_compare_op* comp = il_factor_compare_op_new(self->type);
		comp->parent = self;
		self->u.compare_op = comp;
		il_factor_compare_op_load(comp, env);
	} else if(operator_bit(self->type) || operator_logic(self->type)) {
		self->category = operator_clogic;
		il_factor_logic_op* logic = il_factor_logic_op_new(self->type);
		logic->parent = self;
		self->u.logic_op = logic;
		il_factor_logic_op_load(logic, env);
	} else if(operator_shift(self->type)) {
		self->category = operator_cshift;
		il_factor_shift_op* shift = il_factor_shift_op_new(self->type);
		shift->parent = self;
		self->u.shift_op = shift;
		il_factor_shift_op_load(shift, env);
	} else if(self->type == operator_excor) {
		self->category = operator_cexcor;
		il_factor_excor_op* excor = il_factor_excor_op_new(self->type);
		excor->parent = self;
		self->u.excor_op = excor;
		il_factor_excor_op_load(excor, env);
	} else {
		assert(false);
	}
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env) {
	il_factor_binary_op_load(self, env);
	generic_type* ret = NULL;
	switch(self->category) {
		case operator_carithmeric:
			ret = il_factor_arithmetic_op_eval(self->u.arithmetic_op, env);
			break;
		case operator_ccompare:
			ret = il_factor_compare_op_eval(self->u.compare_op, env);
			break;
		case operator_clogic:
			ret = il_factor_logic_op_eval(self->u.logic_op, env);
			break;
		case operator_cshift:
			ret = il_factor_shift_op_eval(self->u.shift_op, env);
			break;
		case operator_cexcor:
			ret = il_factor_excor_op_eval(self->u.excor_op, env);
			break;
	}
	assert(ret != NULL);
	return ret;
}

char* il_factor_binary_op_tostr(il_factor_binary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->category) {
		case operator_carithmeric:
			ret = il_factor_arithmetic_op_tostr(self->u.arithmetic_op, env);
			break;
		case operator_clogic:
			ret = il_factor_logic_op_tostr(self->u.logic_op, env);
			break;
		case operator_ccompare:
			ret = il_factor_compare_op_tostr(self->u.compare_op, env);
			break;
		case operator_cshift:
			ret = il_factor_shift_op_tostr(self->u.shift_op, env);
			break;
		case operator_cexcor:
			ret = il_factor_excor_op_tostr(self->u.excor_op, env);
			break;
	}
	assert(ret != NULL);
	return ret;
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	switch(self->category) {
		case operator_carithmeric:
			il_factor_arithmetic_op_delete(self->u.arithmetic_op);
			break;
		case operator_clogic:
			il_factor_logic_op_delete(self->u.logic_op);
			break;
		case operator_ccompare:
			il_factor_compare_op_delete(self->u.compare_op);
			break;
		case operator_cshift:
			il_factor_shift_op_delete(self->u.shift_op);
			break;
		case operator_cexcor:
			il_factor_excor_op_delete(self->u.excor_op);
			break;
	}
	MEM_FREE(self);
}

char* il_factor_binary_op_tostr_simple(il_factor_binary_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_appends(sb, il_factor_tostr(self->left, env));
	string_buffer_appendf(sb, " %s ", operator_tostring(self->type));
	string_buffer_appends(sb, il_factor_tostr(self->right, env));
	return string_buffer_release(sb);
}

bool il_factor_binary_op_int_int(il_factor_binary_op* self, enviroment* env) {
	return type_test(self, env, TYPE_INT);
}

bool il_factor_binary_op_double_double(il_factor_binary_op* self, enviroment* env) {
	return type_test(self, env, TYPE_DOUBLE);
}

bool il_factor_binary_op_bool_bool(il_factor_binary_op* self, enviroment* env) {
	return type_test(self, env, TYPE_BOOL);
}

int il_factor_binary_op_index(il_factor_binary_op* self, enviroment* env) {
	vector* args = vector_new();
	generic_type* lgtype = il_factor_eval(self->left, env);
	generic_type* rgtype = il_factor_eval(self->right, env);
	if(il_factor_binary_op_int_int(self, env) ||
	  il_factor_binary_op_double_double(self, env)) {
		  return -1;
	}
	if(lgtype->virtual_type_index != -1) {
		assert(false);
	}
	//vector_push(args, lgtype);
	vector_push(args, rgtype);
	type* lctype = GENERIC2TYPE(lgtype);
	assert(lctype->tag == type_class);
	class_* lclass = TYPE2CLASS(lctype);
	int temp = 0;
	class_find_operator_overload(lclass, self->type, args, env, &temp);
	vector_delete(args, vector_deleter_null);
	return temp;
}

static bool type_test(il_factor_binary_op* self, enviroment* env, type* t) {
	generic_type* lgtype = il_factor_eval(self->left, env);
	generic_type* rgtype = il_factor_eval(self->right, env);
	return GENERIC2TYPE(lgtype) == t &&
	       GENERIC2TYPE(rgtype) == t;
}