#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct Enviroment;
struct type;
struct constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct il_factor_new_instance {
	Vector* argument_list;
	fqcn_cache* fqcnc;
	Vector* type_args;
//	generic_cache* fqcn;
	generic_type* instance_type;
	struct constructor* c;
	int constructor_index;
} il_factor_new_instance;

il_factor* WrapILNewInstance(il_factor_new_instance* self);

il_factor_new_instance* NewILNewInstance();

void GenerateILNewInstance(il_factor_new_instance* self, Enviroment* env, CallContext* cctx);

void LoadILNewInstance(il_factor_new_instance* self, Enviroment* env, CallContext* cctx);

generic_type* EvalILNewInstance(il_factor_new_instance* self, Enviroment* env, CallContext* cctx);

char* ILNewInstanceToString(il_factor_new_instance* self, Enviroment* env);

void DeleteILNewInstance(il_factor_new_instance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
