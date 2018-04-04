#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"
#define IL_FACT2NEW(fact) (il_factor_cast_new_instance(fact))
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

/**
 * コンストラクタの呼び出しを表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_new_instance(il_factor_new_instance* self);

/**
 * コンストラクタの呼び出しを表す要素を作成します.
 * @return
 */
il_factor_new_instance* il_factor_new_instance_new();

/**
 * コンストラクタの呼び出しを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_new_instance_dump(il_factor_new_instance* self, int depth);

/**
 * コンストラクタの呼び出しを表す要素を出力します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_new_instance_generate(il_factor_new_instance* self, struct enviroment* env, il_load_cache* cache);

/**
 * コンストラクタの呼び出しを読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_new_instance_load(il_factor_new_instance* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * コンストラクタで生成されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_new_instance_eval(il_factor_new_instance* self, struct enviroment* env, il_load_cache* cache);

/**
 * コンストラクタの呼び出しを表す要素を開放します.
 * @param self
 */
void il_factor_new_instance_delete(il_factor_new_instance* self);

il_factor_new_instance* il_factor_cast_new_instance(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
