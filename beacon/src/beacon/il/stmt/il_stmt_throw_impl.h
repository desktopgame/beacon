#ifndef BEACON_IL_IL_STM_THROW_H
#define BEACON_IL_IL_STM_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct ILStatement_throw {
	ILFactor* fact;
} ILStatement_throw;

ILStatement* WrapILThrow(ILStatement_throw* self);

ILStatement_throw* NewILThrow();

void GenerateILThrow(ILStatement_throw* self, Enviroment* env, CallContext* cctx);

void LoadILThrow(ILStatement_throw* self, Enviroment* env, CallContext* cctx);

void DeleteILThrow(ILStatement_throw* self);
#endif
