#pragma once
#ifndef BEACON_IL_IL_FACTOR_AS_H
#define BEACON_IL_IL_FACTOR_AS_H
#include "../il_factor_interface.h"
#include "../../env/generic_cache.h"

#define IL_FACT2AS(factor) (il_factor_cast_as(factor))

/**
 * as演算子を表す構造体.
 */
typedef struct il_factor_as {
	il_factor* fact;
	generic_cache* fqcn;
} il_factor_as;

struct enviroment;
struct type;
struct field;

/**
 * as演算子を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_as(il_factor_as* self);

/**
 * 新しいas演算子を作成します.
 * @return
 */
il_factor_as* il_factor_as_new();

/**
 * as演算子をダンプします.
 * @param self
 * @param depth
 */
void il_factor_as_dump(il_factor_as* self, int depth);

/**
 * as演算子を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_as_generate(il_factor_as* self, struct enviroment* env, il_context* ilctx);

/**
 * as演算子を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_as_load(il_factor_as* self, struct enviroment* env, il_context* ilctx);

/**
 * as演算子の型を返します.
 * @param self
 * @param env
 * @return
 */
generic_type* il_factor_as_eval(il_factor_as* self, struct enviroment* env, il_context* ilctx);

/**
 * as演算子を解放します.
 * @param self
 */
void il_factor_as_delete(il_factor_as* self);

il_factor_as* il_factor_cast_as(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_AS_H
