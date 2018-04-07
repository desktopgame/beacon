#pragma once
#ifndef BEACON_IL_IL_FACTOR_INC_H
#define BEACON_IL_IL_FACTOR_INC_H
#include "../il_operator_fixtype.h"
#include "../il_factor_interface.h"
#define IL_FACT2INC(fact) (il_factor_cast_inc(fact))
struct enviroment;
/**
 * インクリメントを表す要素.
 */
typedef struct il_factor_inc {
	il_factor* fact;
	fix_type type;
} il_factor_inc;

/**
 * インクリメントを表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_inc(il_factor_inc* self);

/**
 * インクリメントを表す要素を作成します.
 * @param type
 * @return
 */
il_factor_inc* il_factor_inc_new(fix_type type);

/**
 * インクリメントを表す要素をダンプします.
 * @param self
 * @param depth
 */
void il_factor_inc_dump(il_factor_inc* self, int depth);

/**
 * インクリメントを表す要素を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_inc_generate(il_factor_inc* self, struct enviroment* env, il_context* ilctx);

/**
 * インクリメントを表す要素を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_inc_load(il_factor_inc* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * インクリメントを表す要素の型を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_inc_eval(il_factor_inc* self, struct enviroment* env, il_context* ilctx);

/**
 * インクリメントを表す要素を解放します.
 * @param self
 */
void il_factor_inc_delete(il_factor_inc* self);

il_factor_inc* il_factor_cast_inc(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_INC_H
