#ifndef BEACON_IL_IL_STMT_ASSERT_H
#define BEACON_IL_IL_STMT_ASSERT_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
struct Enviroment;
struct ILStatement;

typedef struct ILAssert {
	ILFactor* Condition;
	ILFactor* Message;
	struct ILStatement* Parent;
} ILAssert;

ILStatement* WrapILAssert(ILAssert* self);

ILAssert* NewILAssert();

void GenerateILAssert(ILAssert* self, Enviroment* env, CallContext* cctx);

void LoadILAssert(ILAssert* self, Enviroment* env, CallContext* cctx);

void DeleteILAssert(ILAssert* self);
#endif