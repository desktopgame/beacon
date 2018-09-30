#pragma once
#ifndef BEACON_IL_IL_FACTOR_VARIABLE_H
#define BEACON_IL_IL_FACTOR_VARIABLE_H
#include "../il_factor_interface.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_type.h"
#include "../../util/vector.h"
#include "variable/il_factor_variable_local_impl.h"
#include "variable/il_factor_variable_static_impl.h"
#include <stdbool.h>

//struct opcode_buf;
struct generic_type;
struct field;

/**
 * 変数の種類を判別する列挙.
 * beaconの構文定義では、次のものは全て一度 il_Variable として変換されます。
 * <code>
 * variable Namespace::Class variable<|T|> Namespace::Class<|T|>
 * </code>
 */
typedef enum il_variable_type {
	ILVARIABLE_TYPE_LOCAL_T,
	ILVARIABLE_TYPE_STATIC_T,
	ILVARIABLE_TYPE_UNDEFINED_T
} il_variable_type;

/**
 * 変数を表す要素.
 */
typedef struct il_factor_variable {
	fqcn_cache* fqcn;
	Vector* type_args;
	int index;
	il_variable_type type;
	union {
		il_factor_variable_local* local_;
		il_factor_variable_static* static_;
	} u;
} il_factor_variable;

il_factor* WrapILVariable(il_factor_variable* self);

#define il_factor_variable_new() (MallocILVariable(__FILE__, __LINE__))
il_factor_variable* MallocILVariable(const char* filename, int lineno);

void GenerateILVariable(il_factor_variable* self, struct enviroment* env, call_context* cctx);

void LoadILVariable(il_factor_variable* self, struct enviroment* env, call_context* cctx);

generic_type* EvalILVariable(il_factor_variable* self, struct enviroment* env, call_context* cctx);

char* ILVariableToString(il_factor_variable* self, struct enviroment* env);

void DeleteILVariable(il_factor_variable* self);

#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
