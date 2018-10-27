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
typedef struct ILAs {
	ILFactor* Source;
	GenericCache* GCache;
	GenericType* GType;
	CastMode Mode;
} ILAs;

struct Enviroment;
struct type;
struct Field;

ILFactor* WrapILAs(ILAs* self);

ILAs* NewILAs();

void GenerateILAs(ILAs* self, Enviroment* env, CallContext* cctx);

void LoadILAs(ILAs* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILAs(ILAs* self, Enviroment* env, CallContext* cctx);

void DeleteILAs(ILAs* self);

char* ILAsToString(ILAs* self, Enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
