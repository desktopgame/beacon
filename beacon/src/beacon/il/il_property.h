#ifndef BEACON_IL_IL_PROPERTY_H
#define BEACON_IL_IL_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "il_property_body.h"
struct generic_cache;

typedef struct il_property {
	struct generic_cache* fqcn;
	access_level access;
	modifier_type modifier;
	string_view namev;
	il_property_body* set;
	il_property_body* get;
} il_property;

#define il_property_new(namev) (il_property_malloc(namev, __FILE__, __LINE__))
il_property* il_property_malloc(string_view namev, const char* filename, int lineno);

void il_property_delete(il_property* self);
#endif