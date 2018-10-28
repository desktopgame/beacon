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

ILFactor * WrapILUnaryOp(ILUnaryOp * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_UNARY_OP_T);
	ret->u.unary_ = self;
	return ret;
}

ILUnaryOp * NewILUnaryOp(OperatorType type) {
	ILUnaryOp* ret = (ILUnaryOp*)MEM_MALLOC(sizeof(ILUnaryOp));
	ret->type = type;
	ret->a = NULL;
	if(type == OPERATOR_NOT_T) ret->u.not_op = NULL;
	if(type == OPERATOR_CHILDA_T) ret->u.childa_op= NULL;
	if(type == OPERATOR_NEGATIVE_T) ret->u.negative_op = NULL;
	return ret;
}

void GenerateILUnaryOp(ILUnaryOp * self, Enviroment* env, CallContext* cctx) {
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

void LoadILUnaryOp(ILUnaryOp * self, Enviroment * env, CallContext* cctx) {
	if(self->type == OPERATOR_NOT_T && self->u.not_op != NULL) return;
	if(self->type == OPERATOR_CHILDA_T && self->u.childa_op != NULL) return;
	if(self->type == OPERATOR_NEGATIVE_T && self->u.negative_op != NULL) return;
	LoadILFactor(self->a, env, cctx);
	//カテゴリーわけ
	if(self->type == OPERATOR_NOT_T) {
		self->category = OPERATOR_CNOT_T;
		ILFactor_not_op* not = NewILNotOp(self->type);
		not->parent = self;
		self->u.not_op = not;
		LoadILNotOp(not, env, cctx);
	} else if(self->type == OPERATOR_NEGATIVE_T) {
		self->category = OPERATOR_NEGATIVE_T;
		ILFactor_negative_op* neg = ILFactor_negative_op_new(self->type);
		neg->parent = self;
		self->u.negative_op = neg;
		LoadILNegativeOp(neg, env, cctx);
	} else if(self->type == OPERATOR_CHILDA_T) {
		self->category = OPERATOR_CCHILDA_T;
		ILFactor_childa_op* childa = NewILChildaOp(self->type);
		childa->parent = self;
		self->u.childa_op = childa;
		LoadILChildaOp(childa, env, cctx);
	} else {
		assert(false);
	}
}

GenericType* EvalILUnaryOp(ILUnaryOp * self, Enviroment * env, CallContext* cctx) {
	LoadILUnaryOp(self, env, cctx);
	GenericType* ret = NULL;
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

char* ILUnaryOpToString(ILUnaryOp* self, Enviroment* env) {
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

void DeleteILUnaryOp(ILUnaryOp * self) {
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

char* ILUnaryOpToString_simple(ILUnaryOp* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->a, env);
	AppendfBuffer(sb, "%s", OperatorToString(self->type));
	AppendsBuffer(sb, a);
	MEM_FREE(a);
	return ReleaseBuffer(sb);
}

int GetIndexILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx) {
	return GetIndexILUnaryOp2(self->a, self->type, env, cctx);
}

int GetIndexILUnaryOp2(ILFactor* receiver, OperatorType otype, Enviroment* env, CallContext* cctx) {
	Vector* args = NewVector();
	GenericType* gtype = EvalILFactor(receiver, env, cctx);
	if(gtype->VirtualTypeIndex != -1) {
		assert(false);
	}
	class_* lclass = TYPE2CLASS(GENERIC2TYPE(gtype));
	int temp = 0;
	GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
	DeleteVector(args, VectorDeleterOfNull);
	return temp;
}

GenericType* ApplyILUnaryOp(ILUnaryOp* self, GenericType* gtype, Enviroment* env, CallContext* cctx) {
	GenericType* lgtype = EvalILFactor(self->a, env, cctx);
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Receiver = lgtype;
	GenericType* ret = ApplyGenericType(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}