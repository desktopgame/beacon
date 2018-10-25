#ifndef BEACON_ENV_PROPERTY_H
#define BEACON_ENV_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "property_body.h"
struct generic_type;
struct type;
struct field;
struct object;

typedef struct Property {
	ModifierType modifier;
	StringView namev;
	struct type* parent;
	struct field* source_ref;
	struct generic_type* gtype;
	AccessLevel access;
	PropertyBody* set;
	PropertyBody* get;
	bool is_short;
} Property;

#define Property_new(namev) (MallocProperty(namev, __FILE__, __LINE__))
Property* MallocProperty(StringView namev, const char* filename, int lineno);

void DeleteProperty(Property* self);
#endif