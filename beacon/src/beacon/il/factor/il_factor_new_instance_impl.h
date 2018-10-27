#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct Enviroment;
struct type;
struct Constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct ILNewInstance {
	Vector* argument_list;
	FQCNCache* fqcnc;
	Vector* type_args;
//	GenericCache* fqcn;
	GenericType* instance_type;
	struct Constructor* c;
	int constructor_index;
} ILNewInstance;

ILFactor* WrapILNewInstance(ILNewInstance* self);

ILNewInstance* NewILNewInstance();

void GenerateILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

void LoadILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILNewInstance(ILNewInstance* self, Enviroment* env, CallContext* cctx);

char* ILNewInstanceToString(ILNewInstance* self, Enviroment* env);

void DeleteILNewInstance(ILNewInstance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
