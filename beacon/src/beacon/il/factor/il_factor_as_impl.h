#pragma once
#ifndef BEACON_IL_IL_FACTOR_AS_H
#define BEACON_IL_IL_FACTOR_AS_H
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"

typedef enum CastMode {
	CAST_DOWN_T,
	CAST_UP_T,
	CAST_UNKNOWN_T,
} CastMode;

/**
 * as演算子を表す構造体.
 */
typedef struct ILFactor_as {
	ILFactor* fact;
	GenericCache* fqcn;
	GenericType* gtype;
	CastMode mode;
} ILFactor_as;

struct Enviroment;
struct type;
struct Field;

ILFactor* WrapILAs(ILFactor_as* self);

ILFactor_as* NewILAs();

void GenerateILAs(ILFactor_as* self, Enviroment* env, CallContext* cctx);

void LoadILAs(ILFactor_as* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILAs(ILFactor_as* self, Enviroment* env, CallContext* cctx);

void DeleteILAs(ILFactor_as* self);

char* ILAsToString(ILFactor_as* self, Enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
