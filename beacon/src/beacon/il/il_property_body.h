#ifndef BEACON_IL_IL_PROPERTY_BODY_H
#define BEACON_IL_IL_PROPERTY_BODY_H
#include "../util/vector.h"
#include "../ast/access_level.h"
#include <stdbool.h>

struct generic_cache;

typedef enum ILPropertyBodyTag {
	ilPROPERTY_SET_T,
	ilPROPERTY_GET_T,
} ILPropertyBodyTag;

typedef struct il_property_body {
	AccessLevel access;
	Vector* statement_list;
	ILPropertyBodyTag tag;
	bool is_short;
} il_property_body;

#define il_property_body_new(tag) (MallocILPropertyBody(tag, __FILE__, __LINE__))
il_property_body* MallocILPropertyBody(ILPropertyBodyTag tag, const char* filename, int lineno);

void DeleteILPropertyBody(il_property_body* self);
#endif