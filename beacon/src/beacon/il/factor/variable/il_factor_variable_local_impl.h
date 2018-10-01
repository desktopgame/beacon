#ifndef BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#define BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#include "../../../util/vector.h"
#include "../../../util/string_pool.h"
#include "../../il_factor_interface.h"
struct symbol_entry;
struct enviroment;
struct generic_type;
struct field;
struct property;

typedef enum variable_local_type {
	VARIABLE_LOCAL_SCOPE_T,
	VARIABLE_LOCAL_FIELD_T,
	VARIABLE_LOCAL_PROPERTY_T,
	VARIABLE_LOCAL_UNDEFINED_T,
} variable_local_type;

typedef struct field_with_index {
	struct field* fi;
	int index;
} field_with_index;

typedef struct property_with_index {
	struct property* p;
	int index;
} property_with_index;

/**
 * ローカル変数を表す構造体.
 */
typedef struct il_factor_variable_local {
	string_view namev;
	variable_local_type type;
	struct generic_type* gt;
	union {
		struct symbol_entry* entry_;
		field_with_index f_with_i;
		property_with_index p_with_i;
	} u;
	Vector* type_args;
} il_factor_variable_local;

il_factor_variable_local* NewILVariableLocal(string_view namev);

void il_factor_variable_local_generate(il_factor_variable_local* self, struct enviroment* env, call_context* cctx);

void il_factor_variable_local_load(il_factor_variable_local * self, struct enviroment * env, call_context* cctx);

struct generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, struct enviroment * env, call_context* cctx);

char* il_factor_variable_local_tostr(il_factor_variable_local * self, struct enviroment * env);

void il_factor_variable_local_delete(il_factor_variable_local* self);
#endif