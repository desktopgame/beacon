#ifndef BEACON_IL_IL_STMT_DEFER_IMPL_H
#define BEACON_IL_IL_STMT_DEFER_IMPL_H
#include "../il_stmt_interface.h"

typedef struct ILDefer {
	ILStatement* Task;
} ILDefer;

ILStatement* WrapILDefer(ILDefer* self);

ILDefer* NewILDefer();

void LoadILDefer(ILDefer* self, Enviroment* env, CallContext* cctx);

void GenerateILDefer(ILDefer* self, Enviroment* env, CallContext* cctx);

void DeleteILDefer(ILDefer* self);
#endif