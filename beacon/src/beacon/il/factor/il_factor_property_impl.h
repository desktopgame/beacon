#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct Enviroment;
struct GenericType;

typedef struct il_factor_Property {
	il_factor* fact;
	StringView namev;
	int index;
	Property* p;
} il_factor_Property;

#define il_factor_Property_new() (MallocILPropertyAccess(__FILE__, __LINE__))
il_factor_Property* MallocILPropertyAccess(const char* filename, int lineno);

void GenerateILPropertyAccess(il_factor_Property* self, Enviroment* env, CallContext* cctx);

void LoadILProperty(il_factor_Property* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILProperty(il_factor_Property* self, Enviroment* env, CallContext* cctx);

char* ILPropertyToString(il_factor_Property* self, Enviroment* env);

void DeleteILPropertyAccess(il_factor_Property* self);
#endif