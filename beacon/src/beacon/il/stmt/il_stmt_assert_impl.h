#ifndef BEACON_IL_IL_STMT_ASSERT_H
#define BEACON_IL_IL_STMT_ASSERT_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct enviroment;

typedef struct il_stmt_assert {
	il_factor* condition;
	il_factor* message;
} il_stmt_assert;

il_stmt* il_stmt_wrap_assert(il_stmt_assert* self);

il_stmt_assert* il_stmt_assert_new();

void il_stmt_assert_dump(il_stmt_assert* self, int depth);

void il_stmt_assert_generate(il_stmt_assert* self, struct enviroment* env, il_context* ilctx);

void il_stmt_assert_load(il_stmt_assert* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

void il_stmt_assert_delete(il_stmt_assert* self);
#endif