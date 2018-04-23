#pragma once
#ifndef BEACON_IL_IL_FACTOR_CAST_H
#define BEACON_IL_IL_FACTOR_CAST_H
#include "../il_factor_interface.h"

#define IL_FACT2CAST(fact) (il_factor_cast_cast(fact))

struct generic_cache;
struct type;
struct enviroment;

/**
 * キャストを表す構造体.
 */
typedef struct il_factor_cast {
	struct generic_cache* fqcn;
	il_factor* fact;
} il_factor_cast;

/**
 * キャストを表す構造体をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_cast(il_factor_cast* self);

/**
 * キャストを表す要素を作成します.
 * @param fact
 * @return
 */
il_factor_cast* il_factor_cast_new(il_factor* fact);

/**
 * キャストを表す要素をダンプします.
 * @param self
 * @param depth
 */
void il_factor_cast_dump(il_factor_cast* self, int depth);

/**
 * キャストを表す要素を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_cast_generate(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

/**
 * キャストを表す要素を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_cast_load(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

/**
 * キャストを表す要素の型を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_cast_eval(il_factor_cast* self, struct enviroment* env, il_context* ilctx);

/**
 * キャストを表す要素を解放します.
 * @param self
 */
void il_factor_cast_delete(il_factor_cast* self);

il_factor_cast* il_factor_cast_cast(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_CAST_H
