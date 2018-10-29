#include "il_factor_logic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"

static Opcode operator_to_iopcode(OperatorType type);
static Opcode operator_to_bopcode(OperatorType type);

ILLogicOp* NewILLogicOp(OperatorType type) {
	ILLogicOp* ret = (ILLogicOp*)MEM_MALLOC(sizeof(ILLogicOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

GenericType* EvalILLogicOp(ILLogicOp* self, Enviroment* env, CallContext* cctx) {
	if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_INT);
	} else if(IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_BOOL);
	} else {
		GenericType* lgtype = EvalILFactor(self->Parent->Left, env, cctx);
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		if(self->OperatorIndex == -1) {
			ThrowBCError(
				BCERROR_UNDEFINED_LOGIC_OPERATOR_T,
				OperatorToString(self->Type)
			);
			return NULL;
		}
		OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->OperatorIndex);
		return ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
	}
}

void GenerateILLogicOp(ILLogicOp* self, Enviroment* env, CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->Type));
		} else if(IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_bopcode(self->Type));
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILLogicOp(ILLogicOp* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
	self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILLogicOp(ILLogicOp* self) {
	MEM_FREE(self);
}

char* ILLogicOpToString(ILLogicOp* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}
//static
static Opcode operator_to_iopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_IBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_IBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_ILOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_ILOGIC_AND;
	}
	assert(false);
}

static Opcode operator_to_bopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_BBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_BBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_BLOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_BLOGIC_AND;
	}
	assert(false);
}