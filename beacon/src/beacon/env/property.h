#ifndef BEACON_ENV_PROPERTY_H
#define BEACON_ENV_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "property_body.h"
struct generic_type;
struct type;
struct Field;
struct Object;

typedef struct Property {
	ModifierType Modifier;
	StringView Name;
	struct type* Parent;
	struct Field* SourceRef;
	struct generic_type* GType;
	AccessLevel Access;
	PropertyBody* Set;
	PropertyBody* Get;
	bool IsShort;
} Property;

#define Property_new(namev) (MallocProperty(namev, __FILE__, __LINE__))
Property* MallocProperty(StringView namev, const char* filename, int lineno);

void DeleteProperty(Property* self);
#endif