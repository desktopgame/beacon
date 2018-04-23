#ifndef BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#define BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#include "../../../util/vector.h"
#include "../../il_factor_interface.h"
struct symbol_entry;
struct enviroment;
struct generic_type;
struct field;

typedef enum variable_local_type {
	variable_local_scope,
	variable_local_field,
	variable_local_undefined,
} variable_local_type;

/**
 * ローカル変数を表す構造体.
 */
typedef struct il_factor_variable_local {
	char* name;
	variable_local_type type;
	struct generic_type* gt;
	union {
		struct symbol_entry* entry_;
		int field_index;
	} u;
	vector* type_args;
} il_factor_variable_local;

il_factor_variable_local* il_factor_variable_local_new(const char* name);

void il_factor_variable_local_generate(il_factor_variable_local* self, struct enviroment* env, il_context* ilctx);

void il_factor_variable_local_load(il_factor_variable_local * self, struct enviroment * env, il_context* ilctx);

struct generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, struct enviroment * env, il_context* ilctx);

void il_factor_variable_local_delete(il_factor_variable_local* self);
#endif