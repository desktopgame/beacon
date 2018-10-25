#ifndef BEACON_ENV_PROPERTY_BODY_H
#define BEACON_ENV_PROPERTY_BODY_H
#include "../ast/access_level.h"
struct Enviroment;
struct property;

typedef enum PropertyBodyTag {
	PROPERTY_SET_T,
	PROPERTY_GET_T
} PropertyBodyTag;

typedef struct property_body {
	struct property* parent;
	AccessLevel access;
	PropertyBodyTag tag;
	struct Enviroment* env;
} property_body;

#define property_body_new(tag) (MallocPropertyBody(tag, __FILE__, __LINE__))
property_body* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno);

void DeletePropertyBody(property_body* self);
#endif