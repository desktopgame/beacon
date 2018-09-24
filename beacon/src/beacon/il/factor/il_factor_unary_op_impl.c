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
	il_factor* ret = il_factor_new(ilfactor_unary_op_T);
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * il_factor_unary_op_new(operator_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)MEM_MALLOC(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	if(type == operator_not_T) ret->u.not_op = NULL;
	if(type == operator_childa_T) ret->u.childa_op= NULL;
	if(type == operator_negative_T) ret->u.negative_op = NULL;
	return ret;
}

void il_factor_unary_op_generate(il_factor_unary_op * self, enviroment* env, call_context* cctx) {
	switch(self->type) {
		case operator_not_T:
			il_factor_not_op_generate(self->u.not_op, env, cctx);
			break;
		case operator_childa_T:
			il_factor_childa_op_generate(self->u.childa_op, env, cctx);
			break;
		case operator_negative_T:
			il_factor_negative_op_generate(self->u.negative_op, env, cctx);
			break;
	}
}

void il_factor_unary_op_load(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
	if(self->type == operator_not_T && self->u.not_op != NULL) return;
	if(self->type == operator_childa_T && self->u.childa_op != NULL) return;
	if(self->type == operator_negative_T && self->u.negative_op != NULL) return;
	il_factor_load(self->a, env, cctx);
	//カテゴリーわけ
	if(self->type == operator_not_T) {
		self->category = operator_cnot_T;
		il_factor_not_op* not = il_factor_not_op_new(self->type);
		not->parent = self;
		self->u.not_op = not;
		il_factor_not_op_load(not, env, cctx);
	} else if(self->type == operator_negative_T) {
		self->category = operator_negative_T;
		il_factor_negative_op* neg = il_factor_negative_op_new(self->type);
		neg->parent = self;
		self->u.negative_op = neg;
		il_factor_negative_op_load(neg, env, cctx);
	} else if(self->type == operator_childa_T) {
		self->category = operator_cchilda_T;
		il_factor_childa_op* childa = il_factor_childa_op_new(self->type);
		childa->parent = self;
		self->u.childa_op = childa;
		il_factor_childa_op_load(childa, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* il_factor_unary_op_eval(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
	il_factor_unary_op_load(self, env, cctx);
	generic_type* ret = NULL;
	switch(self->type) {
		case operator_not_T:
			ret = il_factor_not_op_eval(self->u.not_op, env, cctx);
			break;
		case operator_childa_T:
			ret = il_factor_childa_op_eval(self->u.childa_op, env, cctx);
			break;
		case operator_negative_T:
			ret = il_factor_negative_op_eval(self->u.negative_op, env, cctx);
			break;
	}
	return ret;
}

char* il_factor_unary_op_tostr(il_factor_unary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->type) {
		case operator_not_T:
			ret = il_factor_not_op_tostr(self->u.not_op, env);
			break;
		case operator_childa_T:
			ret = il_factor_childa_op_tostr(self->u.childa_op, env);
			break;
		case operator_negative_T:
			ret = il_factor_negative_op_tostr(self->u.negative_op, env);
			break;
	}
	return ret;
}

void il_factor_unary_op_delete(il_factor_unary_op * self) {
	if(self == NULL) {
		return;
	}
	il_factor_delete(self->a);
	switch(self->type) {
		case operator_not_T:
			il_factor_not_op_delete(self->u.not_op);
			break;
		case operator_childa_T:
			il_factor_childa_op_delete(self->u.childa_op);
			break;
		case operator_negative_T:
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

int il_factor_unary_op_index(il_factor_unary_op* self, enviroment* env, call_context* cctx) {
	return il_factor_unary_op_index2(self->a, self->type, env, cctx);
}

int il_factor_unary_op_index2(il_factor* receiver, operator_type otype, enviroment* env, call_context* cctx) {
	vector* args = vector_new();
	generic_type* gtype = il_factor_eval(receiver, env, cctx);
	if(gtype->virtual_type_index != -1) {
		assert(false);
	}
	class_* lclass = TYPE2CLASS(GENERIC2TYPE(gtype));
	int temp = 0;
	class_gfind_operator_overload(lclass, otype, args, env, cctx, &temp);
	vector_delete(args, vector_deleter_null);
	return temp;
}

generic_type* il_factor_unary_op_apply(il_factor_unary_op* self, generic_type* gtype, enviroment* env, call_context* cctx) {
	generic_type* lgtype = il_factor_eval(self->a, env, cctx);
	call_frame* cfr = call_context_push(cctx, frame_instance_invoke_T);
	cfr->u.instance_invoke.receiver = lgtype;
	generic_type* ret = generic_type_apply(gtype,cctx);
	call_context_pop(cctx);
	return ret;
}