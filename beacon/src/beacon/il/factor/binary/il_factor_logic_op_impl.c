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

static bc_Opcode operator_to_iopcode(bc_OperatorType type);
static bc_Opcode operator_to_bopcode(bc_OperatorType type);

ILLogicOp* NewILLogicOp(bc_OperatorType type) {
	ILLogicOp* ret = (ILLogicOp*)MEM_MALLOC(sizeof(ILLogicOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILLogicOp(ILLogicOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(BC_TYPE_INT);
	} else if(bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
		return bc_TYPE2GENERIC(BC_TYPE_BOOL);
	} else {
		bc_GenericType* lgtype = bc_EvalILFactor(self->Parent->Left, env, cctx);
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		if(self->OperatorIndex == -1) {
			bc_Panic(
				BCERROR_UNDEFINED_LOGIC_OPERATOR_T,
				bc_OperatorToString(self->Type)
			);
			return NULL;
		}
		bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(lgtype)), self->OperatorIndex);
		return bc_ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
	}
}

void GenerateILLogicOp(ILLogicOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		if(bc_IsIntIntBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_iopcode(self->Type));
		} else if(bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
			bc_AddOpcodeBuf(env->Bytecode, (bc_VectorItem)operator_to_bopcode(self->Type));
		} else {
			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Right, env, cctx);
		bc_GenerateILFactor(self->Parent->Left, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILLogicOp(ILLogicOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(!bc_IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !bc_IsBoolBoolBinaryOp(self->Parent, env, cctx)) {
	self->OperatorIndex = bc_GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILLogicOp(ILLogicOp* self) {
	MEM_FREE(self);
}

char* ILLogicOpToString(ILLogicOp* self, bc_Enviroment* env) {
	return bc_ILBinaryOpToStringSimple(self->Parent, env);
}
//static
static bc_Opcode operator_to_iopcode(bc_OperatorType type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_IBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_IBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_ILOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_ILOGIC_AND;
	}
	assert(false);
}

static bc_Opcode operator_to_bopcode(bc_OperatorType type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_BBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_BBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_BLOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_BLOGIC_AND;
	}
	assert(false);
}