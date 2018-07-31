#ifndef BEACON_ENV_PROPERTY_H
#define BEACON_ENV_PROPERTY_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "property_body.h"
struct generic_type;
struct type;
struct object;

typedef struct property {
	modifier_type modifier;
	string_view namev;
	struct type* parent;
	struct generic_type* gtype;
	struct object* static_value;
	access_level access;
	property_body* set;
	property_body* get;
} property;

#define property_new(namev) (property_malloc(namev, __FILE__, __LINE__))
property* property_malloc(string_view namev, const char* filename, int lineno);

void property_delete(property* self);
#endif