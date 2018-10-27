#ifndef BEACON_IL_IL_STMT_ASSERT_H
#define BEACON_IL_IL_STMT_ASSERT_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct Enviroment;
struct ILStatement;

typedef struct ILStatement_assert {
	ILFactor* condition;
	ILFactor* message;
	struct ILStatement* parent;
} ILStatement_assert;

ILStatement* WrapILAssert(ILStatement_assert* self);

ILStatement_assert* NewILAssert();

void GenerateILAssert(ILStatement_assert* self, Enviroment* env, CallContext* cctx);

void LoadILAssert(ILStatement_assert* self, Enviroment* env, CallContext* cctx);

void DeleteILAssert(ILStatement_assert* self);
#endif