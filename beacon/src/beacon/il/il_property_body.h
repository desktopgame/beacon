#ifndef BEACON_IL_IL_PROPERTY_BODY_H
#define BEACON_IL_IL_PROPERTY_BODY_H
#include "../util/vector.h"
#include "../ast/access_level.h"
#include <stdbool.h>

struct generic_cache;

typedef enum il_property_body_tag {
	ilproperty_set,
	ilproperty_get,
} il_property_body_tag;

typedef struct il_property_body {
	access_level access;
	vector* statement_list;
	il_property_body_tag tag;
	bool is_short;
} il_property_body;

#define il_property_body_new(tag) (il_property_body_malloc(tag, __FILE__, __LINE__))
il_property_body* il_property_body_malloc(il_property_body_tag tag, const char* filename, int lineno);

void il_property_body_dump(il_property_body* self, int depth);

void il_property_body_delete(il_property_body* self);
#endif