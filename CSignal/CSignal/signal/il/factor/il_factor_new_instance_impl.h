#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
#define SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../il_factor_interface.h"
struct enviroment;
struct type;
struct constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct il_factor_new_instance {
	vector* argument_list;
	fqcn_cache* fqcn;
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
struct type* il_factor_new_instance_eval(il_factor_new_instance* self, struct enviroment* env, il_load_cache* cache);

/**
 * コンストラクタの呼び出しを表す要素を開放します.
 * @param self
 */
void il_factor_new_instance_delete(il_factor_new_instance* self);
#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
