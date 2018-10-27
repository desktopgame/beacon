#ifndef BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#define BEACON_IL_IL_FACTOR_VARIABLE_LOCAL_H
#include "../../../util/vector.h"
#include "../../../util/string_pool.h"
#include "../../il_factor_interface.h"
struct SymbolEntry;
struct Enviroment;
struct GenericType;
struct Field;
struct Property;

typedef enum variable_local_type {
	VARIABLE_LOCAL_SCOPE_T,
	VARIABLE_LOCAL_FIELD_T,
	VARIABLE_LOCAL_PROPERTY_T,
	VARIABLE_LOCAL_UNDEFINED_T,
} variable_local_type;

typedef struct field_with_index {
	struct Field* fi;
	int index;
} field_with_index;

typedef struct Property_with_index {
	struct Property* p;
	int index;
} Property_with_index;

/**
 * ローカル変数を表す構造体.
 */
typedef struct ILFactor_variable_local {
	StringView namev;
	variable_local_type type;
	struct GenericType* gt;
	union {
		struct SymbolEntry* entry_;
		field_with_index f_with_i;
		Property_with_index p_with_i;
	} u;
	Vector* type_args;
} ILFactor_variable_local;

ILFactor_variable_local* NewILVariableLocal(StringView namev);

void GenerateILVariableLocal(ILFactor_variable_local* self, Enviroment* env, CallContext* cctx);

void LoadILVariableLocal(ILFactor_variable_local * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableLocal(ILFactor_variable_local * self, Enviroment * env, CallContext* cctx);

char* ILVariableLocalToString(ILFactor_variable_local * self, Enviroment * env);

void DeleteILVariableLocal(ILFactor_variable_local* self);
#endif