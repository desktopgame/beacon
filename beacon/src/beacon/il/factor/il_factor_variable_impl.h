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
struct GenericType;
struct Field;

/**
 * 変数の種類を判別する列挙.
 * beaconの構文定義では、次のものは全て一度 il_Variable として変換されます。
 * <code>
 * variable Namespace::Class variable<|T|> Namespace::Class<|T|>
 * </code>
 */
typedef enum ILVariableType {
	ILVARIABLE_TYPE_LOCAL_T,
	ILVARIABLE_TYPE_STATIC_T,
	ILVARIABLE_TYPE_UNDEFINED_T
} ILVariableType;

/**
 * 変数を表す要素.
 */
typedef struct ILFactor_variable {
	FQCNCache* fqcn;
	Vector* type_args;
	int index;
	ILVariableType type;
	union {
		ILFactor_variable_local* local_;
		ILFactor_variable_static* static_;
	} u;
} ILFactor_variable;

ILFactor* WrapILVariable(ILFactor_variable* self);

#define ILFactor_variable_new() (MallocILVariable(__FILE__, __LINE__))
ILFactor_variable* MallocILVariable(const char* filename, int lineno);

void GenerateILVariable(ILFactor_variable* self, Enviroment* env, CallContext* cctx);

void LoadILVariable(ILFactor_variable* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILVariable(ILFactor_variable* self, Enviroment* env, CallContext* cctx);

char* ILVariableToString(ILFactor_variable* self, Enviroment* env);

void DeleteILVariable(ILFactor_variable* self);

#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
