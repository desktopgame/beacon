#ifndef BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#define BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#include "../il_factor_interface.h"
struct GenericType;
typedef struct ILAssignOp {
	ILFactor* Left;
	ILFactor* Right;
} ILAssignOp;

ILFactor* WrapILAssignOp(ILAssignOp* self);

ILAssignOp* NewILAssignOp();

void LoadILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx);

void GenerateILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILAssignOp(ILAssignOp* self, Enviroment* env, CallContext* cctx);

void DeleteILAssignOp(ILAssignOp* self);
#endif