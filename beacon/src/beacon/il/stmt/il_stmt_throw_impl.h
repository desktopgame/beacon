#ifndef BEACON_IL_IL_STM_THROW_H
#define BEACON_IL_IL_STM_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct enviroment;

typedef struct il_stmt_throw {
	il_factor* fact;
} il_stmt_throw;

il_stmt* WrapILThrow(il_stmt_throw* self);

il_stmt_throw* NewILThrow();

void il_stmt_throw_generate(il_stmt_throw* self, struct enviroment* env, call_context* cctx);

void LoadILThrow(il_stmt_throw* self, struct enviroment* env, call_context* cctx);

void DeleteILThrow(il_stmt_throw* self);
#endif
