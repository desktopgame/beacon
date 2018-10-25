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
	struct property* Parent;
	AccessLevel Access;
	PropertyBodyTag Tag;
	struct Enviroment* Env;
} PropertyBody;

#define PropertyBody_new(tag) (MallocPropertyBody(tag, __FILE__, __LINE__))
PropertyBody* MallocPropertyBody(PropertyBodyTag tag, const char* filename, int lineno);

void DeletePropertyBody(PropertyBody* self);
#endif