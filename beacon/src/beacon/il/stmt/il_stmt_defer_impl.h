#ifndef BEACON_IL_IL_STMT_DEFER_IMPL_H
#define BEACON_IL_IL_STMT_DEFER_IMPL_H
#include "../il_stmt_interface.h"

typedef struct il_stmt_defer {
	il_stmt* stmt;
} il_stmt_defer;

il_stmt* il_stmt_wrap_defer(il_stmt_defer* self);

il_stmt_defer* il_stmt_defer_new();

void il_stmt_defer_dump(il_stmt_defer* self, int depth);

void il_stmt_defer_load(il_stmt_defer* self, enviroment* env, call_context* cctx);

void il_stmt_defer_generate(il_stmt_defer* self, enviroment* env, call_context* cctx);

void il_stmt_defer_delete(il_stmt_defer* self);
#endif