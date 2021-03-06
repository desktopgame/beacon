#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct enviroment;
struct generic_type;

typedef struct il_factor_property {
	il_factor* fact;
	string_view namev;
	int index;
	property* p;
} il_factor_property;

#define il_factor_property_new() (il_factor_property_malloc(__FILE__, __LINE__))
il_factor_property* il_factor_property_malloc(const char* filename, int lineno);

void il_factor_property_generate(il_factor_property* self, struct enviroment* env, call_context* cctx);

void il_factor_property_load(il_factor_property* self, struct enviroment* env, call_context* cctx);

struct generic_type* il_factor_property_eval(il_factor_property* self, enviroment* env, call_context* cctx);

char* il_factor_property_tostr(il_factor_property* self, struct enviroment* env);

void il_factor_property_dump(il_factor_property* self, int depth);

void il_factor_property_delete(il_factor_property* self);
#endif