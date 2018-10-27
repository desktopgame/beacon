#ifndef BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#define BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#include "../il_factor_interface.h"
struct GenericCache;
struct GenericType;
struct FQCNCache;

typedef struct ILFactor_instanceof {
	ILFactor* fact;
	struct GenericCache* gcache;
} ILFactor_instanceof;

ILFactor* WrapILInstanceOf(ILFactor_instanceof* self);

ILFactor_instanceof* NewILInstanceOf();

void LoadILInstanceOf(ILFactor_instanceof* self, Enviroment* env, CallContext* cctx);

void GenerateILInstanceOf(ILFactor_instanceof* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILInstanceOf(ILFactor_instanceof* self, Enviroment* env, CallContext* cctx);

char* ILInstanceOfToString(ILFactor_instanceof* self, Enviroment* env);

void DeleteILInstanceOf(ILFactor_instanceof* self);
#endif
