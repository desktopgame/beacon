#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct Enviroment;
struct GenericType;

typedef struct ILFactor_Property {
	ILFactor* fact;
	StringView namev;
	int index;
	Property* p;
} ILFactor_Property;

#define ILFactor_Property_new() (MallocILPropertyAccess(__FILE__, __LINE__))
ILFactor_Property* MallocILPropertyAccess(const char* filename, int lineno);

void GenerateILPropertyAccess(ILFactor_Property* self, Enviroment* env, CallContext* cctx);

void LoadILProperty(ILFactor_Property* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILProperty(ILFactor_Property* self, Enviroment* env, CallContext* cctx);

char* ILPropertyToString(ILFactor_Property* self, Enviroment* env);

void DeleteILPropertyAccess(ILFactor_Property* self);
#endif