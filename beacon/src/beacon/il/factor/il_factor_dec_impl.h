#pragma once
#ifndef BEACON_IL_IL_FACTOR_DEC_H
#define BEACON_IL_IL_FACTOR_DEC_H
#include "../il_operator_fixtype.h"
#include "../il_factor_interface.h"

#define IL_FACT2DEC(fact) (il_factor_cast_dec(fact))

/**
 * デクリメントを表す要素.
 */
typedef struct il_factor_dec {
	il_factor* fact;
	fix_type type;
} il_factor_dec;

/**
 * デクリメントを表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_dec(il_factor_dec* self);

/**
 * デクリメントを表す要素を作成します.
 * @param type
 * @return
 */
il_factor_dec* il_factor_dec_new(fix_type type);

/**
 * デクリメントを表す要素をダンプします.
 * @param self
 * @param depth
 */
void il_factor_dec_dump(il_factor_dec* self, int depth);

/**
 * デクリメントを表す要素を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_dec_generate(il_factor_dec* self, struct enviroment* env, il_context* ilctx);

/**
 * デクリメントを表す要素を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_dec_load(il_factor_dec* self, struct enviroment* env, il_context* ilctx);

/**
 * デクリメントを表す要素の方を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_dec_eval(il_factor_dec* self, struct enviroment* env, il_context* ilctx);

/**
 * デクリメントを表す要素を解放します.
 * @param self
 */
void il_factor_dec_delete(il_factor_dec* self);

il_factor_dec* il_factor_cast_dec(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_DEC_H
