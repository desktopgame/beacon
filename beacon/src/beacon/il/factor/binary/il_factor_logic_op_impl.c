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

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_bopcode(operator_type type);

il_factor_logic_op* NewILLogicOp(operator_type type) {
	il_factor_logic_op* ret = (il_factor_logic_op*)MEM_MALLOC(sizeof(il_factor_logic_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

generic_type* EvalILLogicOp(il_factor_logic_op* self, Enviroment* env, call_context* cctx) {
	if(IsIntIntBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_INT);
	} else if(IsBoolBoolBinaryOp(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_BOOL);
	} else {
		generic_type* lgtype = EvalILFactor(self->parent->left, env, cctx);
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		if(self->operator_index == -1) {
			ThrowBCError(
				BCERROR_UNDEFINED_LOGIC_OPERATOR_T,
				operator_tostring(self->type)
			);
			return NULL;
		}
		operator_overload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
		return ApplyILBinaryOp(self->parent, operator_ov->return_gtype, env, cctx);
	}
}

void GenerateILLogicOp(il_factor_logic_op* self, Enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		if(IsIntIntBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->type));
		} else if(IsBoolBoolBinaryOp(self->parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_bopcode(self->type));
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->parent->right, env, cctx);
		GenerateILFactor(self->parent->left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->operator_index);
	}
}

void LoadILLogicOp(il_factor_logic_op* self, Enviroment* env, call_context* cctx) {
	if(!IsIntIntBinaryOp(self->parent, env, cctx) &&
	   !IsBoolBoolBinaryOp(self->parent, env, cctx)) {
	self->operator_index = GetIndexILBinaryOp(self->parent, env, cctx);
	}
}

void DeleteILLogicOp(il_factor_logic_op* self) {
	MEM_FREE(self);
}

char* ILLogicOpToString(il_factor_logic_op* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_IBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_IBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_ILOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_ILOGIC_AND;
	}
	assert(false);
}

static opcode operator_to_bopcode(operator_type type) {
	switch(type) {
		case OPERATOR_BIT_OR_T: return OP_BBIT_OR;
		case OPERATOR_BIT_AND_T: return OP_BBIT_AND;
		case OPERATOR_LOGIC_OR_T: return OP_BLOGIC_OR;
		case OPERATOR_LOGIC_AND_T: return OP_BLOGIC_AND;
	}
	assert(false);
}