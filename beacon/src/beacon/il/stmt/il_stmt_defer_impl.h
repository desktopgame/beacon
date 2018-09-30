#ifndef BEACON_IL_IL_STMT_DEFER_IMPL_H
#define BEACON_IL_IL_STMT_DEFER_IMPL_H
#include "../il_stmt_interface.h"

typedef struct il_stmt_defer {
	il_stmt* stmt;
} il_stmt_defer;

il_stmt* WrapILDefer(il_stmt_defer* self);

il_stmt_defer* NewILDefer();

void LoadILDefer(il_stmt_defer* self, enviroment* env, call_context* cctx);

void GenerateILDefer(il_stmt_defer* self, enviroment* env, call_context* cctx);

void DeleteILDefer(il_stmt_defer* self);
#endif