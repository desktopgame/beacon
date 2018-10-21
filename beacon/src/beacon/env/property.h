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

typedef struct property {
	ModifierType modifier;
	StringView namev;
	struct type* parent;
	struct field* source_ref;
	struct generic_type* gtype;
	AccessLevel access;
	property_body* set;
	property_body* get;
	bool is_short;
} property;

#define property_new(namev) (MallocProperty(namev, __FILE__, __LINE__))
property* MallocProperty(StringView namev, const char* filename, int lineno);

void DeleteProperty(property* self);
#endif