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

il_factor * WrapILUnaryOp(il_factor_unary_op * self) {
	il_factor* ret = il_factor_new(ILFACTOR_UNARY_OP_T);
	ret->u.unary_ = self;
	return ret;
}

il_factor_unary_op * NewILUnaryOp(operator_type type) {
	il_factor_unary_op* ret = (il_factor_unary_op*)MEM_MALLOC(sizeof(il_factor_unary_op));
	ret->type = type;
	ret->a = NULL;
	if(type == OPERATOR_NOT_T) ret->u.not_op = NULL;
	if(type == OPERATOR_CHILDA_T) ret->u.childa_op= NULL;
	if(type == OPERATOR_NEGATIVE_T) ret->u.negative_op = NULL;
	return ret;
}

void GenerateILUnaryOp(il_factor_unary_op * self, enviroment* env, call_context* cctx) {
	switch(self->type) {
		case OPERATOR_NOT_T:
			GenerateILNotOp(self->u.not_op, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			GenerateILChildaOp(self->u.childa_op, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			GenerateILNegativeOp(self->u.negative_op, env, cctx);
			break;
	}
}

void LoadILUnaryOp(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
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
		LoadILNegativeOp(neg, env, cctx);
	} else if(self->type == OPERATOR_CHILDA_T) {
		self->category = OPERATOR_CCHILDA_T;
		il_factor_childa_op* childa = NewILChildaOp(self->type);
		childa->parent = self;
		self->u.childa_op = childa;
		LoadILChildaOp(childa, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* EvalILUnaryOp(il_factor_unary_op * self, enviroment * env, call_context* cctx) {
	LoadILUnaryOp(self, env, cctx);
	generic_type* ret = NULL;
	switch(self->type) {
		case OPERATOR_NOT_T:
			ret = EvalILNotOp(self->u.not_op, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			ret = EvalILChildaOp(self->u.childa_op, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = EvalILNegativeOp(self->u.negative_op, env, cctx);
			break;
	}
	return ret;
}

char* ILUnaryOpToString(il_factor_unary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->type) {
		case OPERATOR_NOT_T:
			ret = ILNotOpToString(self->u.not_op, env);
			break;
		case OPERATOR_CHILDA_T:
			ret = ILChildaOpToString(self->u.childa_op, env);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = ILNegativeOpToString(self->u.negative_op, env);
			break;
	}
	return ret;
}

void DeleteILUnaryOp(il_factor_unary_op * self) {
	if(self == NULL) {
		return;
	}
	DeleteILFactor(self->a);
	switch(self->type) {
		case OPERATOR_NOT_T:
			DeleteILNotOp(self->u.not_op);
			break;
		case OPERATOR_CHILDA_T:
			DeleteILChildaOp(self->u.childa_op);
			break;
		case OPERATOR_NEGATIVE_T:
			DeleteILNegativeOp(self->u.negative_op);
			break;
	}
	MEM_FREE(self);
}

char* ILUnaryOpToString_simple(il_factor_unary_op* self, enviroment* env) {
	StringBuffer* sb = NewBuffer();
	char* a = ILFactorToString(self->a, env);
	AppendfBuffer(sb, "%s", operator_tostring(self->type));
	AppendsBuffer(sb, a);
	MEM_FREE(a);
	return ReleaseBuffer(sb);
}

int GetIndexILUnaryOp(il_factor_unary_op* self, enviroment* env, call_context* cctx) {
	return GetIndexILUnaryOp2(self->a, self->type, env, cctx);
}

int GetIndexILUnaryOp2(il_factor* receiver, operator_type otype, enviroment* env, call_context* cctx) {
	Vector* args = NewVector();
	generic_type* gtype = EvalILFactor(receiver, env, cctx);
	if(gtype->virtual_type_index != -1) {
		assert(false);
	}
	class_* lclass = TYPE2CLASS(GENERIC2TYPE(gtype));
	int temp = 0;
	GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
	DeleteVector(args, VectorDeleterOfNull);
	return temp;
}

generic_type* ApplyILUnaryOp(il_factor_unary_op* self, generic_type* gtype, enviroment* env, call_context* cctx) {
	generic_type* lgtype = EvalILFactor(self->a, env, cctx);
	call_frame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->u.instance_invoke.receiver = lgtype;
	generic_type* ret = ApplyGenericType(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}