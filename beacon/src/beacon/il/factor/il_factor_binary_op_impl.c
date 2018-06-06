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
	}
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env) {
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
	} else {
		assert(false);
	}
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env) {
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
	}
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
	}
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
	}
	MEM_FREE(self);
}