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
	ret->Type = type;
	ret->Arg = NULL;
	if(type == OPERATOR_NOT_T) ret->Kind.NotOp = NULL;
	if(type == OPERATOR_CHILDA_T) ret->Kind.ChildaOp= NULL;
	if(type == OPERATOR_NEGATIVE_T) ret->Kind.NegativeOp = NULL;
	return ret;
}

void GenerateILUnaryOp(ILUnaryOp * self, Enviroment* env, CallContext* cctx) {
	switch(self->Type) {
		case OPERATOR_NOT_T:
			GenerateILNotOp(self->Kind.NotOp, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			GenerateILChildaOp(self->Kind.ChildaOp, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			GenerateILNegativeOp(self->Kind.NegativeOp, env, cctx);
			break;
	}
}

void LoadILUnaryOp(ILUnaryOp * self, Enviroment * env, CallContext* cctx) {
	if(self->Type == OPERATOR_NOT_T && self->Kind.NotOp != NULL) return;
	if(self->Type == OPERATOR_CHILDA_T && self->Kind.ChildaOp != NULL) return;
	if(self->Type == OPERATOR_NEGATIVE_T && self->Kind.NegativeOp != NULL) return;
	LoadILFactor(self->Arg, env, cctx);
	//カテゴリーわけ
	if(self->Type == OPERATOR_NOT_T) {
		self->Category = OPERATOR_CNOT_T;
		ILFactor_not_op* not = NewILNotOp(self->Type);
		not->parent = self;
		self->Kind.NotOp = not;
		LoadILNotOp(not, env, cctx);
	} else if(self->Type == OPERATOR_NEGATIVE_T) {
		self->Category = OPERATOR_NEGATIVE_T;
		ILNegativeOp* neg = ILNegativeOp_new(self->Type);
		neg->Parent = self;
		self->Kind.NegativeOp = neg;
		LoadILNegativeOp(neg, env, cctx);
	} else if(self->Type == OPERATOR_CHILDA_T) {
		self->Category = OPERATOR_CCHILDA_T;
		ILChildaOp* childa = NewILChildaOp(self->Type);
		childa->Parent = self;
		self->Kind.ChildaOp = childa;
		LoadILChildaOp(childa, env, cctx);
	} else {
		assert(false);
	}
}

GenericType* EvalILUnaryOp(ILUnaryOp * self, Enviroment * env, CallContext* cctx) {
	LoadILUnaryOp(self, env, cctx);
	GenericType* ret = NULL;
	switch(self->Type) {
		case OPERATOR_NOT_T:
			ret = EvalILNotOp(self->Kind.NotOp, env, cctx);
			break;
		case OPERATOR_CHILDA_T:
			ret = EvalILChildaOp(self->Kind.ChildaOp, env, cctx);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = EvalILNegativeOp(self->Kind.NegativeOp, env, cctx);
			break;
	}
	return ret;
}

char* ILUnaryOpToString(ILUnaryOp* self, Enviroment* env) {
	char* ret = NULL;
	switch(self->Type) {
		case OPERATOR_NOT_T:
			ret = ILNotOpToString(self->Kind.NotOp, env);
			break;
		case OPERATOR_CHILDA_T:
			ret = ILChildaOpToString(self->Kind.ChildaOp, env);
			break;
		case OPERATOR_NEGATIVE_T:
			ret = ILNegativeOpToString(self->Kind.NegativeOp, env);
			break;
	}
	return ret;
}

void DeleteILUnaryOp(ILUnaryOp * self) {
	if(self == NULL) {
		return;
	}
	DeleteILFactor(self->Arg);
	switch(self->Type) {
		case OPERATOR_NOT_T:
			DeleteILNotOp(self->Kind.NotOp);
			break;
		case OPERATOR_CHILDA_T:
			DeleteILChildaOp(self->Kind.ChildaOp);
			break;
		case OPERATOR_NEGATIVE_T:
			DeleteILNegativeOp(self->Kind.NegativeOp);
			break;
	}
	MEM_FREE(self);
}

char* ILUnaryOpToString_simple(ILUnaryOp* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->Arg, env);
	AppendfBuffer(sb, "%s", OperatorToString(self->Type));
	AppendsBuffer(sb, a);
	MEM_FREE(a);
	return ReleaseBuffer(sb);
}

int GetIndexILUnaryOp(ILUnaryOp* self, Enviroment* env, CallContext* cctx) {
	return GetIndexILUnaryOp2(self->Arg, self->Type, env, cctx);
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
	GenericType* lgtype = EvalILFactor(self->Arg, env, cctx);
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Receiver = lgtype;
	GenericType* ret = ApplyGenericType(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}