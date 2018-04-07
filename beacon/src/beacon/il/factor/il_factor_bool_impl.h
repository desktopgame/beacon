#pragma once
#ifndef BEACON_IL_IL_FACTOR_BOOL_H
#define BEACON_IL_IL_FACTOR_BOOL_H
#include <stdbool.h>
#include "../il_factor_interface.h"

#define IL_FACT2BOOL(fact) (il_factor_cast_bool(fact))

struct enviroment;
struct type;
/**
 * boolリテラルを表す要素.
 */
typedef struct il_factor_bool {
	bool a;
} il_factor_bool;

/**
 * boolリテラルを表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_bool(il_factor_bool* self);

/**
 * boolリテラルを表す要素を作成します.
 * @param b
 * @return
 */
il_factor_bool* il_factor_bool_new(bool b);

/**
 * boolリテラルを表す要素をダンプします.
 * @param self
 * @param depth
 */
void il_factor_bool_dump(il_factor_bool* self, int depth);

/**
 * boolリテラルを表す要素を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_bool_generate(il_factor_bool* self, struct enviroment* env, il_context* ilctx);

/**
 * boolを返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_bool_eval(il_factor_bool* self, struct enviroment* env, il_context* ilctx);

/**
 * boolリテラルを表す要素を解放します.
 * @param self
 */
void il_factor_bool_delete(il_factor_bool* self);

il_factor_bool* il_factor_cast_bool(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_BOOL_H
