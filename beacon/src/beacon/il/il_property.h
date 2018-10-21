#ifndef BEACON_IL_IL_PROPERTY_H
#define BEACON_IL_IL_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "il_property_body.h"
struct generic_cache;

typedef struct il_property {
	struct generic_cache* fqcn;
	AccessLevel access;
	ModifierType modifier;
	StringView namev;
	il_property_body* set;
	il_property_body* get;
} il_property;

#define il_property_new(namev) (MallocILProperty(namev, __FILE__, __LINE__))
il_property* MallocILProperty(StringView namev, const char* filename, int lineno);

void DeleteILProperty(il_property* self);
#endif