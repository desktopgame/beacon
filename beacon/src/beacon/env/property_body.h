#ifndef BEACON_ENV_PROPERTY_BODY_H
#define BEACON_ENV_PROPERTY_BODY_H
#include "../ast/access_level.h"
struct enviroment;

typedef enum property_body_tag {
	property_set,
	property_get
} property_body_tag;

typedef struct property_body {
	access_level access;
	property_body_tag tag;
	struct enviroment* env;
} property_body;

#define property_body_new(tag) (property_body_malloc(tag, __FILE__, __LINE__))
property_body* property_body_malloc(property_body_tag tag, const char* filename, int lineno);

void property_body_delete(property_body* self);
#endif