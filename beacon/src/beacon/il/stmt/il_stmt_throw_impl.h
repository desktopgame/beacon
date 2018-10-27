#ifndef BEACON_IL_IL_STM_THROW_H
#define BEACON_IL_IL_STM_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct il_stmt_throw {
	ILFactor* fact;
} il_stmt_throw;

il_stmt* WrapILThrow(il_stmt_throw* self);

il_stmt_throw* NewILThrow();

void GenerateILThrow(il_stmt_throw* self, Enviroment* env, CallContext* cctx);

void LoadILThrow(il_stmt_throw* self, Enviroment* env, CallContext* cctx);

void DeleteILThrow(il_stmt_throw* self);
#endif
