#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct enviroment;
struct generic_type;

typedef struct il_factor_property {
	il_factor* fact;
	StringView namev;
	int index;
	property* p;
} il_factor_property;

#define il_factor_property_new() (MallocILPropertyAccess(__FILE__, __LINE__))
il_factor_property* MallocILPropertyAccess(const char* filename, int lineno);

void GenerateILPropertyAccess(il_factor_property* self, struct enviroment* env, call_context* cctx);

void LoadILProperty(il_factor_property* self, struct enviroment* env, call_context* cctx);

struct generic_type* EvalILProperty(il_factor_property* self, enviroment* env, call_context* cctx);

char* ILPropertyToString(il_factor_property* self, struct enviroment* env);

void DeleteILPropertyAccess(il_factor_property* self);
#endif