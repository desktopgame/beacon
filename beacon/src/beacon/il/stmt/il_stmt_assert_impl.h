#ifndef BEACON_IL_IL_STMT_ASSERT_H
#define BEACON_IL_IL_STMT_ASSERT_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct Enviroment;
struct il_stmt;

typedef struct il_stmt_assert {
	ILFactor* condition;
	ILFactor* message;
	struct il_stmt* parent;
} il_stmt_assert;

il_stmt* WrapILAssert(il_stmt_assert* self);

il_stmt_assert* NewILAssert();

void GenerateILAssert(il_stmt_assert* self, Enviroment* env, CallContext* cctx);

void LoadILAssert(il_stmt_assert* self, Enviroment* env, CallContext* cctx);

void DeleteILAssert(il_stmt_assert* self);
#endif