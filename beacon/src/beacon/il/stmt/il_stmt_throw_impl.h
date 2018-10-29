#ifndef BEACON_IL_IL_STM_THROW_H
#define BEACON_IL_IL_STM_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct Enviroment;

typedef struct ILThrow {
	ILFactor* Factor;
} ILThrow;

ILStatement* WrapILThrow(ILThrow* self);

ILThrow* NewILThrow();

void GenerateILThrow(ILThrow* self, Enviroment* env, CallContext* cctx);

void LoadILThrow(ILThrow* self, Enviroment* env, CallContext* cctx);

void DeleteILThrow(ILThrow* self);
#endif
