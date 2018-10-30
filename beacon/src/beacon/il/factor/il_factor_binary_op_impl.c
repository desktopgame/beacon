#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include "../il_factor_impl.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/field.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../util/mem.h"
#include "binary/il_factor_arithmetic_op_impl.h"
#include "binary/il_factor_compare_op_impl.h"
//#include "binary/ILAssignOp_impl.h"
#include "binary/il_factor_logic_op_impl.h"
#include "binary/il_factor_shift_op_impl.h"
#include "binary/il_factor_excor_op_impl.h"

static bool type_test(ILBinaryOp* self, Enviroment* env, CallContext* cctx, Type* t);

ILFactor * WrapILBinaryOp(ILBinaryOp * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_BINARY_OP_T);
	ret->Kind.BinaryOp = self;
	return ret;
}

ILBinaryOp * NewILBinaryOp(OperatorType type) {
	ILBinaryOp* ret = (ILBinaryOp*)MEM_MALLOC(sizeof(ILBinaryOp));
	ret->Type = type;
	ret->Left = NULL;
	ret->Right = NULL;
	ret->IsLoaded = false;
	return ret;
}

void GenerateILBinaryOp(ILBinaryOp * self, Enviroment* env, CallContext* cctx) {
	switch(self->Category) {
		case OPERATOR_CARITHMERIC_T:
			GenerateILArithmeticOp(self->Kind.ArithmeticOp, env, cctx);
			break;
		case OPERATOR_CCOMPARE_T:
			GenerateILCompareOp(self->Kind.CompareOp, env, cctx);
			break;
		case OPERATOR_CLOGIC_T:
			GenerateILLogicOp(self->Kind.LogicOp, env, cctx);
			break;
		case OPERATOR_CSHIFT_T:
			GenerateILShiftOp(self->Kind.ShiftOp, env, cctx);
			break;
		case OPERATOR_CEXCOR_T:
			GenerateILExcorOp(self->Kind.ExcorOp, env, cctx);
			break;
	}
}

void LoadILBinaryOp(ILBinaryOp * self, Enviroment * env, CallContext* cctx) {
	if(self->IsLoaded) {
		return;
	}
	self->IsLoaded = true;
	LoadILFactor(self->Left, env, cctx);
	BC_ERROR();
	LoadILFactor(self->Right, env, cctx);
	BC_ERROR();
	//カテゴリーわけ
	if(IsArithmeticOperator(self->Type)) {
		self->Category = OPERATOR_CARITHMERIC_T;
		ILArithmeticOp* arith = NewILArithmeticOp(self->Type);
		arith->Parent = self;
		self->Kind.ArithmeticOp = arith;
		LoadILArithmeticOp(arith, env, cctx);
	} else if(IsCompareOperator(self->Type)) {
		self->Category = OPERATOR_CCOMPARE_T;
		ILCompareOp* comp = NewILCompareOp(self->Type);
		comp->Parent = self;
		self->Kind.CompareOp = comp;
		LoadILCompareOp(comp, env, cctx);
	} else if(IsBitOperator(self->Type) || IsLogicOperator(self->Type)) {
		self->Category = OPERATOR_CLOGIC_T;
		ILLogicOp* logic = NewILLogicOp(self->Type);
		logic->Parent = self;
		self->Kind.LogicOp = logic;
		LoadILLogicOp(logic, env, cctx);
	} else if(IsShiftOperator(self->Type)) {
		self->Category = OPERATOR_CSHIFT_T;
		ILShiftOp* shift = NewILShiftOp(self->Type);
		shift->Parent = self;
		self->Kind.ShiftOp = shift;
		LoadILShiftOp(shift, env, cctx);
	} else if(self->Type == OPERATOR_EXCOR_T) {
		self->Category = OPERATOR_CEXCOR_T;
		ILExcorOp* excor = NewILExcorOp(self->Type);
		excor->Parent = self;
		self->Kind.ExcorOp = excor;
		LoadILExcorOp(excor, env, cctx);
	} else {
		assert(false);
	}
}

GenericType* EvalILBinaryOp(ILBinaryOp * self, Enviroment * env, CallContext* cctx) {
	LoadILBinaryOp(self, env, cctx);
	GenericType* ret = NULL;
	switch(self->Category) {
		case OPERATOR_CARITHMERIC_T:
			ret = EvalILArithmeticOp(self->Kind.ArithmeticOp, env, cctx);
			break;
		case OPERATOR_CCOMPARE_T:
			ret = EvalILCompareOp(self->Kind.CompareOp, env, cctx);
			break;
		case OPERATOR_CLOGIC_T:
			ret = EvalILLogicOp(self->Kind.LogicOp, env, cctx);
			break;
		case OPERATOR_CSHIFT_T:
			ret = EvalILShiftOp(self->Kind.ShiftOp, env, cctx);
			break;
		case OPERATOR_CEXCOR_T:
			ret = EvalILExcorOp(self->Kind.ExcorOp, env, cctx);
			break;
	}
//	assert(ret != NULL);
	return ret;
}

char* ILBinaryOpToString(ILBinaryOp* self, Enviroment* env) {
	char* ret = NULL;
	switch(self->Category) {
		case OPERATOR_CARITHMERIC_T:
			ret = ILArithmeticOpToString(self->Kind.ArithmeticOp, env);
			break;
		case OPERATOR_CLOGIC_T:
			ret = ILLogicOpToString(self->Kind.LogicOp, env);
			break;
		case OPERATOR_CCOMPARE_T:
			ret = ILCompareOpToString(self->Kind.CompareOp, env);
			break;
		case OPERATOR_CSHIFT_T:
			ret = ILShiftOpToString(self->Kind.ShiftOp, env);
			break;
		case OPERATOR_CEXCOR_T:
			ret = ILExcorOpToString(self->Kind.ExcorOp, env);
			break;
	}
	assert(ret != NULL);
	return ret;
}

void DeleteILBinaryOp(ILBinaryOp * self) {
	switch(self->Category) {
		case OPERATOR_CARITHMERIC_T:
			DeleteILArithmeticOp(self->Kind.ArithmeticOp);
			break;
		case OPERATOR_CLOGIC_T:
			DeleteILLogicOp(self->Kind.LogicOp);
			break;
		case OPERATOR_CCOMPARE_T:
			DeleteILCompareOp(self->Kind.CompareOp);
			break;
		case OPERATOR_CSHIFT_T:
			DeleteILShiftOp(self->Kind.ShiftOp);
			break;
		case OPERATOR_CEXCOR_T:
			DeleteILExcorOp(self->Kind.ExcorOp);
			break;
	}
	DeleteILFactor(self->Left);
	DeleteILFactor(self->Right);
	MEM_FREE(self);
}

char* ILBinaryOpToString_simple(ILBinaryOp* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->Left, env);
	char* b = ILFactorToString(self->Right, env);
	AppendsBuffer(sb, a);
	AppendfBuffer(sb, " %s ", OperatorToString(self->Type));
	AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return ReleaseBuffer(sb);
}

bool IsIntIntBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx) {
	return type_test(self, env, cctx, TYPE_INT);
}

bool IsDoubleDoubleBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx) {
	return type_test(self, env, cctx, TYPE_DOUBLE);
}

bool IsBoolBoolBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx) {
	return type_test(self, env, cctx, TYPE_BOOL);
}

bool IsCharCharBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx) {
	return type_test(self, env, cctx, TYPE_CHAR);
}

int GetIndexILBinaryOp(ILBinaryOp* self, Enviroment* env, CallContext* cctx) {
	if(IsIntIntBinaryOp(self, env, cctx) ||
	  IsDoubleDoubleBinaryOp(self, env, cctx)) {
		  return -1;
	}
	return GetIndexILBinaryOp2(self->Left, self->Right, self->Type, env, cctx);
}

int GetIndexILBinaryOp2(ILFactor* receiver, ILFactor* arg, OperatorType otype, Enviroment* env, CallContext* cctx) {
	Vector* args = NewVector();
	GenericType* lgtype = EvalILFactor(receiver, env, cctx);
	GenericType* rgtype = EvalILFactor(arg, env, cctx);
	
	if(lgtype->VirtualTypeIndex != -1) {
		assert(false);
	}
	//PushVector(args, lgtype);
	PushVector(args, rgtype);
	Type* lctype = GENERIC2TYPE(lgtype);
	assert(lctype->Tag == TYPE_CLASS_T);
	Class* lclass = TYPE2CLASS(lctype);
	int temp = 0;
	GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
	DeleteVector(args, VectorDeleterOfNull);
	return temp;
}

GenericType* ApplyILBinaryOp(ILBinaryOp* self, GenericType* gtype, Enviroment* env, CallContext* cctx) {
	GenericType* lgtype = EvalILFactor(self->Left, env, cctx);
	CallFrame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->Kind.InstanceInvoke.Receiver = lgtype;
	GenericType* ret = ApplyGenericType(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}

//private
static bool type_test(ILBinaryOp* self, Enviroment* env, CallContext* cctx, Type* t) {
	GenericType* lgtype = EvalILFactor(self->Left, env, cctx);
	GenericType* rgtype = EvalILFactor(self->Right, env, cctx);
	return GENERIC2TYPE(lgtype) == t &&
	       GENERIC2TYPE(rgtype) == t;
}