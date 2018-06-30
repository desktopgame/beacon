#include "il_factor_unary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_impl.h"
#include "../../util/mem.h"
#include "unary/il_factor_childa_op_impl.h"
#include "unary/il_factor_negative_op_impl.h"
#include "unary/il_factor_not_op_impl.h"

il_factor * il_factor_wrap_unary(il_factor_unary_op * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_unary_op;
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * il_factor_unary_op_new(operator_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)MEM_MALLOC(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	if(type == operator_not) ret->u.not_op = NULL;
	if(type == operator_childa) ret->u.childa_op= NULL;
	if(type == operator_negative) ret->u.negative_op = NULL;
	return ret;
}

void il_factor_unary_op_dump(il_factor_unary_op * self, int depth) {
	switch(self->type) {
		case operator_not:
			il_factor_not_op_dump(self->u.not_op, depth);
			break;
		case operator_childa:
			il_factor_childa_op_dump(self->u.childa_op, depth);
			break;
		case operator_negative:
			il_factor_negative_op_dump(self->u.negative_op, depth);
			break;
	}
	il_factor_dump(self->a, depth + 1);
}

void il_factor_unary_op_generate(il_factor_unary_op * self, enviroment* env) {
	switch(self->type) {
		case operator_not:
			il_factor_not_op_generate(self->u.not_op, env);
			break;
		case operator_childa:
			il_factor_childa_op_generate(self->u.childa_op, env);
			break;
		case operator_negative:
			il_factor_negative_op_generate(self->u.negative_op, env);
			break;
	}
}

void il_factor_unary_op_load(il_factor_unary_op * self, enviroment * env) {
	if(self->type == operator_not && self->u.not_op != NULL) return;
	if(self->type == operator_childa && self->u.childa_op != NULL) return;
	if(self->type == operator_negative && self->u.negative_op != NULL) return;
	il_factor_load(self->a, env);
	//カテゴリーわけ
	if(self->type == operator_not) {
		self->category = operator_cnot;
		il_factor_not_op* not = il_factor_not_op_new(self->type);
		not->parent = self;
		self->u.not_op = not;
		il_factor_not_op_load(not, env);
	} else if(self->type == operator_negative) {
		self->category = operator_negative;
		il_factor_negative_op* neg = il_factor_negative_op_new(self->type);
		neg->parent = self;
		self->u.negative_op = neg;
		il_factor_negative_op_load(neg, env);
	} else if(self->type == operator_childa) {
		self->category = operator_cchilda;
		il_factor_childa_op* childa = il_factor_childa_op_new(self->type);
		childa->parent = self;
		self->u.childa_op = childa;
		il_factor_childa_op_load(childa, env);
	} else {
		assert(false);
	}
}

generic_type* il_factor_unary_op_eval(il_factor_unary_op * self, enviroment * env) {
	il_factor_unary_op_load(self, env);
	generic_type* ret = NULL;
	switch(self->type) {
		case operator_not:
			ret = il_factor_not_op_eval(self->u.not_op, env);
			break;
		case operator_childa:
			ret = il_factor_childa_op_eval(self->u.childa_op, env);
			break;
		case operator_negative:
			ret = il_factor_negative_op_eval(self->u.negative_op, env);
			break;
	}
	return ret;
}

char* il_factor_unary_op_tostr(il_factor_unary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->type) {
		case operator_not:
			ret = il_factor_not_op_tostr(self->u.not_op, env);
			break;
		case operator_childa:
			ret = il_factor_childa_op_tostr(self->u.childa_op, env);
			break;
		case operator_negative:
			ret = il_factor_negative_op_tostr(self->u.negative_op, env);
			break;
	}
	return ret;
}

void il_factor_unary_op_delete(il_factor_unary_op * self) {
	il_factor_delete(self->a);
	switch(self->type) {
		case operator_not:
			il_factor_not_op_delete(self->u.not_op);
			break;
		case operator_childa:
			il_factor_childa_op_delete(self->u.childa_op);
			break;
		case operator_negative:
			il_factor_negative_op_delete(self->u.negative_op);
			break;
	}
	MEM_FREE(self);
}

char* il_factor_unary_op_tostr_simple(il_factor_unary_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* a = il_factor_tostr(self->a, env);
	string_buffer_appendf(sb, "%s", operator_tostring(self->type));
	string_buffer_appends(sb, a);
	MEM_FREE(a);
	return string_buffer_release(sb);
}

il_factor_unary_op* il_factor_cast_unary_op(il_factor* fact) {
	assert(fact->type == ilfactor_unary_op);
	return fact->u.unary_;
}

int il_factor_unary_op_index(il_factor_unary_op* self, enviroment* env) {
	return il_factor_unary_op_index2(self->a, self->type, env);
}

int il_factor_unary_op_index2(il_factor* receiver, operator_type otype, enviroment* env) {
	vector* args = vector_new();
	generic_type* gtype = il_factor_eval(receiver, env);
	if(gtype->virtual_type_index != -1) {
		assert(false);
	}
	class_* lclass = TYPE2CLASS(GENERIC2TYPE(gtype));
	int temp = 0;
	class_find_operator_overload(lclass, otype, args, env, &temp);
	vector_delete(args, vector_deleter_null);
	return temp;
}