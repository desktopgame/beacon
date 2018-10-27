#ifndef BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#define BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#include "../il_factor_interface.h"
struct GenericType;
typedef struct ILFactor_assign_op {
	ILFactor* left;
	ILFactor* right;
} ILFactor_assign_op;

ILFactor* WrapILAssignOp(ILFactor_assign_op* self);

ILFactor_assign_op* NewILAssignOp();

void LoadILAssignOp(ILFactor_assign_op* self, Enviroment* env, CallContext* cctx);

void GenerateILAssignOp(ILFactor_assign_op* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILAssignOp(ILFactor_assign_op* self, Enviroment* env, CallContext* cctx);

void DeleteILAssignOp(ILFactor_assign_op* self);
#endif