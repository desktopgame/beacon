#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../il_ehandler.h"
#include "../il_context.h"
#include "../../env/generic_type.h"
struct enviroment;
struct type;
/**
 * thisを表す要素.
 */
typedef struct il_factor_this {
	generic_type* resolved;
} il_factor_this;

il_factor_this* il_factor_this_new();

/**
 * thisを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_this_dump(il_factor_this* self, int depth);

/**
 * thisを表す要素を出力します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_this_generate(il_factor_this* self, struct enviroment* env, il_context* ilctx);

/**
 * thisを読み込みます.
 * @param self
 * @parma env
 * @param cache
 * @param eh
 */
void il_factor_this_load(il_factor_this* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * thisで参照されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_this_eval(il_factor_this* self, struct enviroment* env, il_context* ilctx);

/**
 * thisを表す要素を開放します.
 * @param self
 */
void il_factor_this_delete(il_factor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
