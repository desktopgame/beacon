#ifndef BEACON_IL_IL_STMT_DEFER_IMPL_H
#define BEACON_IL_IL_STMT_DEFER_IMPL_H
#include "../il_stmt_interface.h"

typedef struct ILStatement_defer {
	ILStatement* stmt;
} ILStatement_defer;

ILStatement* WrapILDefer(ILStatement_defer* self);

ILStatement_defer* NewILDefer();

void LoadILDefer(ILStatement_defer* self, Enviroment* env, CallContext* cctx);

void GenerateILDefer(ILStatement_defer* self, Enviroment* env, CallContext* cctx);

void DeleteILDefer(ILStatement_defer* self);
#endif