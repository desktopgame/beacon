#ifndef BEACON_ENV_PROPERTY_BODY_H
#define BEACON_ENV_PROPERTY_BODY_H
#include "../ast/access_level.h"
struct Enviroment;
struct property;

typedef enum property_body_tag {
	PROPERTY_SET_T,
	PROPERTY_GET_T
} property_body_tag;

typedef struct property_body {
	struct property* parent;
	access_level access;
	property_body_tag tag;
	struct Enviroment* env;
} property_body;

#define property_body_new(tag) (MallocPropertyBody(tag, __FILE__, __LINE__))
property_body* MallocPropertyBody(property_body_tag tag, const char* filename, int lineno);

void DeletePropertyBody(property_body* self);
#endif