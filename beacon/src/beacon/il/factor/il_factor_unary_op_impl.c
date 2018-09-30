#include "il_factor_unary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/TYPE_IMPL.h"
#include "../../util/mem.h"
#include "unary/il_factor_childa_op_impl.h"
#include "unary/il_factor_negative_op_impl.h"
#include "unary/il_factor_not_op_impl.h"

il_factor * WrapILUnary(il_factor_unary_op * self) {
	il_factor* ret = il_factor_new(ILFACTOR_UNARY_OP_T);
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * il_factor_unary_op_new(operator_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)MEM_MALLOC(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	if(type == OPERATOR_NOT_T) ret->u.not_op = NULL;
	if(type == OPERATOR_CHILDA_T) ret->u.childa_op= NULL;
	if(type == OPERATOR_NEGATIVE_T) ret->u.negative_op = NULL;
	return ret;
}

void il_factor_unary_op_generate(il_factor_unary_op * self, enviroment* env, call_context* cctx) {
	switch(self->type) {
		case OPERATOR_NOT_T:
			il_factor_not_op_generate(self->u.not_op, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			il_factor_childa_op_generate(self->u.childa_op, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			il_factor_negative_op_generate(self->u.negative_op, env, cctx);
			break;
	}
}

void il_factor_unary_OP_LOAD(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
	if(self->type == OPERATOR_NOT_T && self->u.not_op != NULL) return;
	if(self->type == OPERATOR_CHILDA_T && self->u.childa_op != NULL) return;
	if(self->type == OPERATOR_NEGATIVE_T && self->u.negative_op != NULL) return;
	LoadILFactor(self->a, env, cctx);
	//カテゴリーわけ
	if(self->type == OPERATOR_NOT_T) {
		self->category = OPERATOR_CNOT_T;
		il_factor_not_op* not = NewILNotOp(self->type);
		not->parent = self;
		self->u.not_op = not;
		LoadILNotOp(not, env, cctx);
	} else if(self->type == OPERATOR_NEGATIVE_T) {
		self->category = OPERATOR_NEGATIVE_T;
		il_factor_negative_op* neg = il_factor_negative_op_new(self->type);
		neg->parent = self;
		self->u.negative_op = neg;
		il_factor_negative_OP_LOAD(neg, env, cctx);
	} else if(self->type == OPERATOR_CHILDA_T) {
		self->category = OPERATOR_CCHILDA_T;
		il_factor_childa_op* childa = il_factor_childa_op_new(self->type);
		childa->parent = self;
		self->u.childa_op = childa;
		il_factor_childa_OP_LOAD(childa, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* il_factor_unary_op_eval(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
	il_factor_unary_OP_LOAD(self, env, cctx);
	generic_type* ret = NULL;
	switch(self->type) {
		case OPERATOR_NOT_T:
			ret = EvalILNotOp(self->u.not_op, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			ret = il_factor_childa_op_eval(self->u.childa_op, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = il_factor_negative_op_eval(self->u.negative_op, env, cctx);
			break;
	}
	return ret;
}

char* il_factor_unary_op_tostr(il_factor_unary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->type) {
		case OPERATOR_NOT_T:
			ret = il_factor_not_op_tostr(self->u.not_op, env);
			break;
		case OPERATOR_CHILDA_T:
			ret = il_factor_childa_op_tostr(self->u.childa_op, env);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = il_factor_negative_op_tostr(self->u.negative_op, env);
			break;
	}
	return ret;
}

void il_factor_unary_op_delete(il_factor_unary_op * self) {
	if(self == NULL) {
		return;
	}
	DeleteILFactor(self->a);
	switch(self->type) {
		case OPERATOR_NOT_T:
			il_factor_not_op_delete(self->u.not_op);
			break;
		case OPERATOR_CHILDA_T:
			il_factor_childa_op_delete(self->u.childa_op);
			break;
		case OPERATOR_NEGATIVE_T:
			il_factor_negative_op_delete(self->u.negative_op);
			break;
	}
	MEM_FREE(self);
}

char* il_factor_unary_op_tostr_simple(il_factor_unary_op* self, enviroment* env) {
	string_buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->a, env);
	AppendfBuffer(sb, "%s", operator_tostring(self->type));
	AppendsBuffer(sb, a);
	MEM_FREE(a);
	return ReleaseBuffer(sb);
}

int il_factor_unary_op_index(il_factor_unary_op* self, enviroment* env, call_context* cctx) {
	return il_factor_unary_op_index2(self->a, self->type, env, cctx);
}

int il_factor_unary_op_index2(il_factor* receiver, operator_type otype, enviroment* env, call_context* cctx) {
	Vector* args = NewVector();
	generic_type* gtype = EvalILFactor(receiver, env, cctx);
	if(gtype->virtual_type_index != -1) {
		assert(false);
	}
	class_* lclass = TYPE2CLASS(GENERIC2TYPE(gtype));
	int temp = 0;
	class_gfind_operator_overload(lclass, otype, args, env, cctx, &temp);
	DeleteVector(args, VectorDeleterOfNull);
	return temp;
}

generic_type* il_factor_unary_op_apply(il_factor_unary_op* self, generic_type* gtype, enviroment* env, call_context* cctx) {
	generic_type* lgtype = EvalILFactor(self->a, env, cctx);
	call_frame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->u.instance_invoke.receiver = lgtype;
	generic_type* ret = generic_type_apply(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}