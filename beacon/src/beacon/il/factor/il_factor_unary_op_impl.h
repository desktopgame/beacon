//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_unary_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_UNARY_OP_H
#define BEACON_IL_IL_FACTOR_UNARY_OP_H
#include "../il_factor_interface.h"
#include "../../env/generic_type.h"
#include "../../ast/operator_type.h"

//struct opcode_buf;
struct ILChildaOp;
struct ILNegativeOp;
struct ILNotOp;

/**
 * 単項演算子を表す要素.
 */
typedef struct bc_ILUnaryOp {
	bc_OperatorType Type;
	bc_OperatorCategory Category;
	bc_ILFactor* Arg;
	union {
		struct ILChildaOp* ChildaOp;
		struct ILNegativeOp* NegativeOp;
		struct ILNotOp* NotOp;
	} Kind;
} bc_ILUnaryOp;

bc_ILFactor* bc_WrapILUnaryOp(bc_ILUnaryOp* self);

bc_ILUnaryOp* bc_NewILUnaryOp(bc_OperatorType type);

void bc_GenerateILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx);

void bc_LoadILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx);

bc_GenericType* bc_EvalILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx);

char* bc_ILUnaryOpToString(bc_ILUnaryOp* self, bc_Enviroment* env);

void bc_DeleteILUnaryOp(bc_ILUnaryOp* self);

char* bc_ILUnaryOpToStringSimple(bc_ILUnaryOp* self, bc_Enviroment* env);

int bc_GetIndexILUnaryOp(bc_ILUnaryOp* self, bc_Enviroment* env, bc_CallContext* cctx);

int bc_GetIndexILUnaryOp2(bc_ILFactor* receiver, bc_OperatorType otype, bc_Enviroment* env, bc_CallContext* cctx);

bc_GenericType* bc_ApplyILUnaryOp(bc_ILUnaryOp* self, bc_GenericType* gtype, bc_Enviroment* env, bc_CallContext* cctx);
#endif // !SIGNAL_IL_IL_FACTOR_UNARY_OP_H
