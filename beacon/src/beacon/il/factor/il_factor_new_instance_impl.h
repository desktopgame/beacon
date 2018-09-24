#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct enviroment;
struct type;
struct constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct il_factor_new_instance {
	vector* argument_list;
	fqcn_cache* fqcnc;
	vector* type_args;
//	generic_cache* fqcn;
	generic_type* instance_type;
	struct constructor* c;
	int constructor_index;
} il_factor_new_instance;

il_factor* il_factor_wrap_new_instance(il_factor_new_instance* self);

il_factor_new_instance* il_factor_new_instance_new();

void il_factor_new_instance_generate(il_factor_new_instance* self, struct enviroment* env, call_context* cctx);

void il_factor_new_instance_load(il_factor_new_instance* self, struct enviroment* env, call_context* cctx);

generic_type* il_factor_new_instance_eval(il_factor_new_instance* self, struct enviroment* env, call_context* cctx);

char* il_factor_new_instance_tostr(il_factor_new_instance* self, struct enviroment* env);

void il_factor_new_instance_delete(il_factor_new_instance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
