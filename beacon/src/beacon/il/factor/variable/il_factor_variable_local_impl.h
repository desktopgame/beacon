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

typedef enum VariableLocalType {
	VARIABLE_LOCAL_SCOPE_T,
	VARIABLE_LOCAL_FIELD_T,
	VARIABLE_LOCAL_PROPERTY_T,
	VARIABLE_LOCAL_UNDEFINED_T,
} VariableLocalType;

typedef struct FieldWithIndex {
	struct Field* fi;
	int index;
} FieldWithIndex;

typedef struct PropertyWithIndex {
	struct Property* p;
	int index;
} PropertyWithIndex;

/**
 * ローカル変数を表す構造体.
 */
typedef struct ILVariableLocal {
	StringView namev;
	VariableLocalType type;
	struct GenericType* gt;
	union {
		struct SymbolEntry* entry_;
		FieldWithIndex f_with_i;
		PropertyWithIndex p_with_i;
	} u;
	Vector* type_args;
} ILVariableLocal;

ILVariableLocal* NewILVariableLocal(StringView namev);

void GenerateILVariableLocal(ILVariableLocal* self, Enviroment* env, CallContext* cctx);

void LoadILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILVariableLocal(ILVariableLocal * self, Enviroment * env, CallContext* cctx);

char* ILVariableLocalToString(ILVariableLocal * self, Enviroment * env);

void DeleteILVariableLocal(ILVariableLocal* self);
#endif