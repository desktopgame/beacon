#ifndef BEACON_IL_YIELD_RETURN_H
#define BEACON_IL_YIELD_RETURN_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

typedef struct ILStatement_yield_return {
	ILFactor* fact;
} ILStatement_yield_return;

ILStatement* WrapILYieldReturn(ILStatement_yield_return* self);

#define ILStatement_yield_return_new() (MallocILYieldReturn(__FILE__, __LINE__))
ILStatement_yield_return* MallocILYieldReturn(const char* filename, int lineno);

void GenerateILYieldReturn(ILStatement_yield_return* self, Enviroment* env, CallContext* cctx);

void LoadILYieldReturn(ILStatement_yield_return * self, Enviroment* env, CallContext* cctx);

void DeleteILYieldReturn(ILStatement_yield_return* self);
#endif