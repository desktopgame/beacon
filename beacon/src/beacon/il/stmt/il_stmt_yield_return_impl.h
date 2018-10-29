#ifndef BEACON_IL_YIELD_RETURN_H
#define BEACON_IL_YIELD_RETURN_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"

typedef struct ILYieldReturn {
	ILFactor* fact;
} ILYieldReturn;

ILStatement* WrapILYieldReturn(ILYieldReturn* self);

#define ILYieldReturn_new() (MallocILYieldReturn(__FILE__, __LINE__))
ILYieldReturn* MallocILYieldReturn(const char* filename, int lineno);

void GenerateILYieldReturn(ILYieldReturn* self, Enviroment* env, CallContext* cctx);

void LoadILYieldReturn(ILYieldReturn * self, Enviroment* env, CallContext* cctx);

void DeleteILYieldReturn(ILYieldReturn* self);
#endif