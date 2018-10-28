#ifndef BEACON_IL_FACTOR_PROPERTY_H
#define BEACON_IL_FACTOR_PROPERTY_H
#include "../il_factor_interface.h"
#include "../../env/property.h"

struct Enviroment;
struct GenericType;

typedef struct ILPropertyAccess {
	ILFactor* fact;
	StringView namev;
	int index;
	Property* p;
} ILPropertyAccess;

#define ILPropertyAccess_new() (MallocILPropertyAccess(__FILE__, __LINE__))
ILPropertyAccess* MallocILPropertyAccess(const char* filename, int lineno);

void GenerateILPropertyAccess(ILPropertyAccess* self, Enviroment* env, CallContext* cctx);

void LoadILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx);

char* ILPropertyToString(ILPropertyAccess* self, Enviroment* env);

void DeleteILPropertyAccess(ILPropertyAccess* self);
#endif