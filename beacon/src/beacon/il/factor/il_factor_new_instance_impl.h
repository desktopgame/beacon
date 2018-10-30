#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct Enviroment;
struct Type;
struct Constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct ILNewInstance {
	Vector* Arguments;
	FQCNCache* FQCNCache;
	Vector* TypeArgs;
//	GenericCache* fqcn;
	GenericType* InstanceGType;
	struct Constructor* Constructor;
	int ConstructorIndex;
} ILNewInstance;

ILFactor* WrapILNewInstance(ILNewInstance* self);

ILNewInstance* NewILNewInstance();

void GenerateILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

void LoadILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

char* ILNewInstanceToString(ILNewInstance* self, Enviroment* env);

void DeleteILNewInstance(ILNewInstance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
