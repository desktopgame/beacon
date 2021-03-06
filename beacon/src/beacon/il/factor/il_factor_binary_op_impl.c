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

static bool type_test(il_factor_binary_op* self, enviroment* env, call_context* cctx, type* t);

il_factor * il_factor_wrap_binary(il_factor_binary_op * self) {
	il_factor* ret = il_factor_new(ilfactor_binary_op_T);
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
		case operator_carithmeric_T:
			il_factor_arithmetic_op_dump(self->u.arithmetic_op, depth);
			break;
		case operator_ccompare_T:
			il_factor_compare_op_dump(self->u.compare_op, depth);
			break;
		case operator_clogic_T:
			il_factor_logic_op_dump(self->u.logic_op, depth);
			break;
		case operator_cshift_T:
			il_factor_shift_op_dump(self->u.shift_op, depth);
			break;
		case operator_cexcor_T:
			il_factor_excor_op_dump(self->u.excor_op, depth);
			break;
	}
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env, call_context* cctx) {
	switch(self->category) {
		case operator_carithmeric_T:
			il_factor_arithmetic_op_generate(self->u.arithmetic_op, env, cctx);
			break;
		case operator_ccompare_T:
			il_factor_compare_op_generate(self->u.compare_op, env, cctx);
			break;
		case operator_clogic_T:
			il_factor_logic_op_generate(self->u.logic_op, env, cctx);
			break;
		case operator_cshift_T:
			il_factor_shift_op_generate(self->u.shift_op, env, cctx);
			break;
		case operator_cexcor_T:
			il_factor_excor_op_generate(self->u.excor_op, env, cctx);
			break;
	}
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env, call_context* cctx) {
	if(self->load) {
		return;
	}
	self->load = true;
	il_factor_load(self->left, env, cctx);
	BC_ERROR();
	il_factor_load(self->right, env, cctx);
	BC_ERROR();
	//カテゴリーわけ
	if(operator_arithmetic(self->type)) {
		self->category = operator_carithmeric_T;
		il_factor_arithmetic_op* arith = il_factor_arithmetic_op_new(self->type);
		arith->parent = self;
		self->u.arithmetic_op = arith;
		il_factor_arithmetic_op_load(arith, env, cctx);
	} else if(operator_compare(self->type)) {
		self->category = operator_ccompare_T;
		il_factor_compare_op* comp = il_factor_compare_op_new(self->type);
		comp->parent = self;
		self->u.compare_op = comp;
		il_factor_compare_op_load(comp, env, cctx);
	} else if(operator_bit(self->type) || operator_logic(self->type)) {
		self->category = operator_clogic_T;
		il_factor_logic_op* logic = il_factor_logic_op_new(self->type);
		logic->parent = self;
		self->u.logic_op = logic;
		il_factor_logic_op_load(logic, env, cctx);
	} else if(operator_shift(self->type)) {
		self->category = operator_cshift_T;
		il_factor_shift_op* shift = il_factor_shift_op_new(self->type);
		shift->parent = self;
		self->u.shift_op = shift;
		il_factor_shift_op_load(shift, env, cctx);
	} else if(self->type == operator_excor_T) {
		self->category = operator_cexcor_T;
		il_factor_excor_op* excor = il_factor_excor_op_new(self->type);
		excor->parent = self;
		self->u.excor_op = excor;
		il_factor_excor_op_load(excor, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env, call_context* cctx) {
	il_factor_binary_op_load(self, env, cctx);
	generic_type* ret = NULL;
	switch(self->category) {
		case operator_carithmeric_T:
			ret = il_factor_arithmetic_op_eval(self->u.arithmetic_op, env, cctx);
			break;
		case operator_ccompare_T:
			ret = il_factor_compare_op_eval(self->u.compare_op, env, cctx);
			break;
		case operator_clogic_T:
			ret = il_factor_logic_op_eval(self->u.logic_op, env, cctx);
			break;
		case operator_cshift_T:
			ret = il_factor_shift_op_eval(self->u.shift_op, env, cctx);
			break;
		case operator_cexcor_T:
			ret = il_factor_excor_op_eval(self->u.excor_op, env, cctx);
			break;
	}
//	assert(ret != NULL);
	return ret;
}

char* il_factor_binary_op_tostr(il_factor_binary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->category) {
		case operator_carithmeric_T:
			ret = il_factor_arithmetic_op_tostr(self->u.arithmetic_op, env);
			break;
		case operator_clogic_T:
			ret = il_factor_logic_op_tostr(self->u.logic_op, env);
			break;
		case operator_ccompare_T:
			ret = il_factor_compare_op_tostr(self->u.compare_op, env);
			break;
		case operator_cshift_T:
			ret = il_factor_shift_op_tostr(self->u.shift_op, env);
			break;
		case operator_cexcor_T:
			ret = il_factor_excor_op_tostr(self->u.excor_op, env);
			break;
	}
	assert(ret != NULL);
	return ret;
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	switch(self->category) {
		case operator_carithmeric_T:
			il_factor_arithmetic_op_delete(self->u.arithmetic_op);
			break;
		case operator_clogic_T:
			il_factor_logic_op_delete(self->u.logic_op);
			break;
		case operator_ccompare_T:
			il_factor_compare_op_delete(self->u.compare_op);
			break;
		case operator_cshift_T:
			il_factor_shift_op_delete(self->u.shift_op);
			break;
		case operator_cexcor_T:
			il_factor_excor_op_delete(self->u.excor_op);
			break;
	}
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}

char* il_factor_binary_op_tostr_simple(il_factor_binary_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* a = il_factor_tostr(self->left, env);
	char* b = il_factor_tostr(self->right, env);
	string_buffer_appends(sb, a);
	string_buffer_appendf(sb, " %s ", operator_tostring(self->type));
	string_buffer_appends(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return string_buffer_release(sb);
}

bool il_factor_binary_op_int_int(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_INT);
}

bool il_factor_binary_op_double_double(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_DOUBLE);
}

bool il_factor_binary_op_bool_bool(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_BOOL);
}

bool il_factor_binary_op_char_char(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_CHAR);
}

int il_factor_binary_op_index(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	if(il_factor_binary_op_int_int(self, env, cctx) ||
	  il_factor_binary_op_double_double(self, env, cctx)) {
		  return -1;
	}
	return il_factor_binary_op_index2(self->left, self->right, self->type, env, cctx);
}

int il_factor_binary_op_index2(il_factor* receiver, il_factor* arg, operator_type otype, enviroment* env, call_context* cctx) {
	vector* args = vector_new();
	generic_type* lgtype = il_factor_eval(receiver, env, cctx);
	generic_type* rgtype = il_factor_eval(arg, env, cctx);
	
	if(lgtype->virtual_type_index != -1) {
		assert(false);
	}
	//vector_push(args, lgtype);
	vector_push(args, rgtype);
	type* lctype = GENERIC2TYPE(lgtype);
	assert(lctype->tag == type_class_T);
	class_* lclass = TYPE2CLASS(lctype);
	int temp = 0;
	class_gfind_operator_overload(lclass, otype, args, env, cctx, &temp);
	vector_delete(args, vector_deleter_null);
	return temp;
}

generic_type* il_factor_binary_op_apply(il_factor_binary_op* self, generic_type* gtype, enviroment* env, call_context* cctx) {
	generic_type* lgtype = il_factor_eval(self->left, env, cctx);
	call_frame* cfr = call_context_push(cctx, frame_instance_invoke_T);
	cfr->u.instance_invoke.receiver = lgtype;
	generic_type* ret = generic_type_apply(gtype,cctx);
	call_context_pop(cctx);
	return ret;
}

//private
static bool type_test(il_factor_binary_op* self, enviroment* env, call_context* cctx, type* t) {
	generic_type* lgtype = il_factor_eval(self->left, env, cctx);
	generic_type* rgtype = il_factor_eval(self->right, env, cctx);
	return GENERIC2TYPE(lgtype) == t &&
	       GENERIC2TYPE(rgtype) == t;
}