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
//#include "binary/il_factor_assign_op_impl.h"
#include "binary/il_factor_logic_op_impl.h"
#include "binary/il_factor_shift_op_impl.h"
#include "binary/il_factor_excor_op_impl.h"

static bool type_test(il_factor_binary_op* self, enviroment* env, call_context* cctx, type* t);

il_factor * WrapILBinaryOp(il_factor_binary_op * self) {
	il_factor* ret = il_factor_new(ILFACTOR_BINARY_OP_T);
	ret->u.binary_ = self;
	return ret;
}

il_factor_binary_op * NewILBinaryOp(operator_type type) {
	il_factor_binary_op* ret = (il_factor_binary_op*)MEM_MALLOC(sizeof(il_factor_binary_op));
	ret->type = type;
	ret->left = NULL;
	ret->right = NULL;
	ret->load = false;
	return ret;
}

void GenerateILBinaryOp(il_factor_binary_op * self, enviroment* env, call_context* cctx) {
	switch(self->category) {
		case OPERATOR_CARITHMERIC_T:
			GenerateILArithmeticOp(self->u.arithmetic_op, env, cctx);
			break;
		case OPERATOR_CCOMPARE_T:
			GenerateILCompareOp(self->u.compare_op, env, cctx);
			break;
		case OPERATOR_CLOGIC_T:
			GenerateILLogicOp(self->u.logic_op, env, cctx);
			break;
		case OPERATOR_CSHIFT_T:
			GenerateILShiftOp(self->u.shift_op, env, cctx);
			break;
		case OPERATOR_CEXCOR_T:
			GenerateILExcorOp(self->u.excor_op, env, cctx);
			break;
	}
}

void LoadILBinaryOp(il_factor_binary_op * self, enviroment * env, call_context* cctx) {
	if(self->load) {
		return;
	}
	self->load = true;
	LoadILFactor(self->left, env, cctx);
	BC_ERROR();
	LoadILFactor(self->right, env, cctx);
	BC_ERROR();
	//カテゴリーわけ
	if(operator_arithmetic(self->type)) {
		self->category = OPERATOR_CARITHMERIC_T;
		il_factor_arithmetic_op* arith = NewILArithmeticOp(self->type);
		arith->parent = self;
		self->u.arithmetic_op = arith;
		LoadILArithmeticOp(arith, env, cctx);
	} else if(operator_compare(self->type)) {
		self->category = OPERATOR_CCOMPARE_T;
		il_factor_compare_op* comp = NewILCompareOp(self->type);
		comp->parent = self;
		self->u.compare_op = comp;
		LoadILCompareOp(comp, env, cctx);
	} else if(operator_bit(self->type) || operator_logic(self->type)) {
		self->category = OPERATOR_CLOGIC_T;
		il_factor_logic_op* logic = NewILLogicOp(self->type);
		logic->parent = self;
		self->u.logic_op = logic;
		LoadILLogicOp(logic, env, cctx);
	} else if(operator_shift(self->type)) {
		self->category = OPERATOR_CSHIFT_T;
		il_factor_shift_op* shift = NewILShiftOp(self->type);
		shift->parent = self;
		self->u.shift_op = shift;
		LoadILShiftOp(shift, env, cctx);
	} else if(self->type == OPERATOR_EXCOR_T) {
		self->category = OPERATOR_CEXCOR_T;
		il_factor_excor_op* excor = NewILExcorOp(self->type);
		excor->parent = self;
		self->u.excor_op = excor;
		LoadILExcorOp(excor, env, cctx);
	} else {
		assert(false);
	}
}

generic_type* EvalILBinaryOp(il_factor_binary_op * self, enviroment * env, call_context* cctx) {
	LoadILBinaryOp(self, env, cctx);
	generic_type* ret = NULL;
	switch(self->category) {
		case OPERATOR_CARITHMERIC_T:
			ret = EvalILArithmeticOp(self->u.arithmetic_op, env, cctx);
			break;
		case OPERATOR_CCOMPARE_T:
			ret = EvalILCompareOp(self->u.compare_op, env, cctx);
			break;
		case OPERATOR_CLOGIC_T:
			ret = EvalILLogicOp(self->u.logic_op, env, cctx);
			break;
		case OPERATOR_CSHIFT_T:
			ret = EvalILShiftOp(self->u.shift_op, env, cctx);
			break;
		case OPERATOR_CEXCOR_T:
			ret = EvalILExcorOp(self->u.excor_op, env, cctx);
			break;
	}
//	assert(ret != NULL);
	return ret;
}

char* ILBinaryOpToString(il_factor_binary_op* self, enviroment* env) {
	char* ret = NULL;
	switch(self->category) {
		case OPERATOR_CARITHMERIC_T:
			ret = ILArithmeticOpToString(self->u.arithmetic_op, env);
			break;
		case OPERATOR_CLOGIC_T:
			ret = ILLogicOpToString(self->u.logic_op, env);
			break;
		case OPERATOR_CCOMPARE_T:
			ret = ILCompareOpToString(self->u.compare_op, env);
			break;
		case OPERATOR_CSHIFT_T:
			ret = ILShiftOpToString(self->u.shift_op, env);
			break;
		case OPERATOR_CEXCOR_T:
			ret = ILExcorOpToString(self->u.excor_op, env);
			break;
	}
	assert(ret != NULL);
	return ret;
}

void DeleteILBinaryOp(il_factor_binary_op * self) {
	switch(self->category) {
		case OPERATOR_CARITHMERIC_T:
			DeleteILArithmeticOp(self->u.arithmetic_op);
			break;
		case OPERATOR_CLOGIC_T:
			DeleteILLogicOp(self->u.logic_op);
			break;
		case OPERATOR_CCOMPARE_T:
			DeleteILCompareOp(self->u.compare_op);
			break;
		case OPERATOR_CSHIFT_T:
			DeleteILShiftOp(self->u.shift_op);
			break;
		case OPERATOR_CEXCOR_T:
			DeleteILExcorOp(self->u.excor_op);
			break;
	}
	DeleteILFactor(self->left);
	DeleteILFactor(self->right);
	MEM_FREE(self);
}

char* ILBinaryOpToString_simple(il_factor_binary_op* self, enviroment* env) {
	Buffer* sb = NewBuffer();
	char* a = ILFactorToString(self->left, env);
	char* b = ILFactorToString(self->right, env);
	AppendsBuffer(sb, a);
	AppendfBuffer(sb, " %s ", operator_tostring(self->type));
	AppendsBuffer(sb, b);
	MEM_FREE(a);
	MEM_FREE(b);
	return ReleaseBuffer(sb);
}

bool IsIntIntBinaryOp(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_INT);
}

bool IsDoubleDoubleBinaryOp(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_DOUBLE);
}

bool IsBoolBoolBinaryOp(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_BOOL);
}

bool IsCharCharBinaryOp(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	return type_test(self, env, cctx, TYPE_CHAR);
}

int GetIndexILBinaryOp(il_factor_binary_op* self, enviroment* env, call_context* cctx) {
	if(IsIntIntBinaryOp(self, env, cctx) ||
	  IsDoubleDoubleBinaryOp(self, env, cctx)) {
		  return -1;
	}
	return GetIndexILBinaryOp2(self->left, self->right, self->type, env, cctx);
}

int GetIndexILBinaryOp2(il_factor* receiver, il_factor* arg, operator_type otype, enviroment* env, call_context* cctx) {
	Vector* args = NewVector();
	generic_type* lgtype = EvalILFactor(receiver, env, cctx);
	generic_type* rgtype = EvalILFactor(arg, env, cctx);
	
	if(lgtype->virtual_type_index != -1) {
		assert(false);
	}
	//PushVector(args, lgtype);
	PushVector(args, rgtype);
	type* lctype = GENERIC2TYPE(lgtype);
	assert(lctype->tag == TYPE_CLASS_T);
	class_* lclass = TYPE2CLASS(lctype);
	int temp = 0;
	GFindOperatorOverloadClass(lclass, otype, args, env, cctx, &temp);
	DeleteVector(args, VectorDeleterOfNull);
	return temp;
}

generic_type* ApplyILBinaryOp(il_factor_binary_op* self, generic_type* gtype, enviroment* env, call_context* cctx) {
	generic_type* lgtype = EvalILFactor(self->left, env, cctx);
	call_frame* cfr = PushCallContext(cctx, FRAME_INSTANCE_INVOKE_T);
	cfr->u.instance_invoke.receiver = lgtype;
	generic_type* ret = ApplyGenericType(gtype,cctx);
	PopCallContext(cctx);
	return ret;
}

//private
static bool type_test(il_factor_binary_op* self, enviroment* env, call_context* cctx, type* t) {
	generic_type* lgtype = EvalILFactor(self->left, env, cctx);
	generic_type* rgtype = EvalILFactor(self->right, env, cctx);
	return GENERIC2TYPE(lgtype) == t &&
	       GENERIC2TYPE(rgtype) == t;
}