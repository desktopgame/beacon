#ifndef BEACON_ENV_PROPERTY_BODY_H
#define BEACON_ENV_PROPERTY_BODY_H
#include "../ast/access_level.h"
struct Enviroment;
struct property;

typedef enum PropertyBodyTag {
	PROPERTY_SET_T,
	PROPERTY_GET_T
} PropertyBodyTag;

typedef struct PropertyBody {
	struct property* parent;
	AccessLevel access;
	PropertyBodyTag tag;
	struct Enviroment* env;
} PropertyBody;

#define PropertyBody_new(tag) (MallocPropertyBody(tag, __FILE__, __LINE__))
PropertyBody* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno);

void DeletePropertyBody(PropertyBody* self);
#endif