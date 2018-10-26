#ifndef BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#define BEACON_IL_IL_FACTOR_ASSIGN_OP_IMPL_H
#include "../il_factor_interface.h"
struct GenericType;
typedef struct il_factor_assign_op {
	il_factor* left;
	il_factor* right;
} il_factor_assign_op;

il_factor* WrapILAssignOp(il_factor_assign_op* self);

il_factor_assign_op* NewILAssignOp();

void LoadILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);

void GenerateILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILAssignOp(il_factor_assign_op* self, Enviroment* env, CallContext* cctx);

void DeleteILAssignOp(il_factor_assign_op* self);
#endif