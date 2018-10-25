#ifndef BEACON_IL_IL_PROPERTY_H
#define BEACON_IL_IL_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "il_property_body.h"
struct generic_cache;

typedef struct ILProperty {
	struct generic_cache* fqcn;
	AccessLevel access;
	ModifierType modifier;
	StringView namev;
	ILPropertyBody* set;
	ILPropertyBody* get;
} ILProperty;

#define ILProperty_new(namev) (MallocILProperty(namev, __FILE__, __LINE__))
ILProperty* MallocILProperty(StringView namev, const char* filename, int lineno);

void DeleteILProperty(ILProperty* self);
#endif