#ifndef BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#define BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#include "../il_factor_interface.h"
struct GenericCache;
struct GenericType;
struct FQCNCache;

typedef struct ILInstanceOf {
	ILFactor* Source;
	struct GenericCache* GCache;
} ILInstanceOf;

ILFactor* WrapILInstanceOf(ILInstanceOf* self);

ILInstanceOf* NewILInstanceOf();

void LoadILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx);

void GenerateILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx);

struct GenericType* EvalILInstanceOf(ILInstanceOf* self, Enviroment* env, CallContext* cctx);

char* ILInstanceOfToString(ILInstanceOf* self, Enviroment* env);

void DeleteILInstanceOf(ILInstanceOf* self);
#endif
