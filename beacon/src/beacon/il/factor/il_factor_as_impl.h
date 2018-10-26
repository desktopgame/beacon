#pragma once
#ifndef BEACON_IL_IL_FACTOR_AS_H
#define BEACON_IL_IL_FACTOR_AS_H
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"
#include "../../env/generic_type.h"

typedef enum cast_mode {
	CAST_DOWN_T,
	CAST_UP_T,
	CAST_UNKNOWN_T,
} cast_mode;

/**
 * as演算子を表す構造体.
 */
typedef struct il_factor_as {
	il_factor* fact;
	GenericCache* fqcn;
	generic_type* gtype;
	cast_mode mode;
} il_factor_as;

struct Enviroment;
struct type;
struct Field;

il_factor* WrapILAs(il_factor_as* self);

il_factor_as* NewILAs();

void GenerateILAs(il_factor_as* self, Enviroment* env, CallContext* cctx);

void LoadILAs(il_factor_as* self, Enviroment* env, CallContext* cctx);

generic_type* EvalILAs(il_factor_as* self, Enviroment* env, CallContext* cctx);

void DeleteILAs(il_factor_as* self);

char* ILAsToString(il_factor_as* self, Enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
