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
typedef struct ILFactor_new_instance {
	Vector* argument_list;
	FQCNCache* fqcnc;
	Vector* type_args;
//	GenericCache* fqcn;
	GenericType* instance_type;
	struct Constructor* c;
	int constructor_index;
} ILFactor_new_instance;

ILFactor* WrapILNewInstance(ILFactor_new_instance* self);

ILFactor_new_instance* NewILNewInstance();

void GenerateILNewInstance(ILFactor_new_instance* self, Enviroment* env, CallContext* cctx);

void LoadILNewInstance(ILFactor_new_instance* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILNewInstance(ILFactor_new_instance* self, Enviroment* env, CallContext* cctx);

char* ILNewInstanceToString(ILFactor_new_instance* self, Enviroment* env);

void DeleteILNewInstance(ILFactor_new_instance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
