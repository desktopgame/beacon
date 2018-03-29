#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../il_ehandler.h"
#include "../il_load_cache.h"
#include "../../env/generic_type.h"
struct enviroment;
struct type;
/**
 * thisを表す要素.
 */
typedef int il_factor_this;

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
void il_factor_this_generate(il_factor_this* self, struct enviroment* env, il_load_cache* cache);

/**
 * thisを読み込みます.
 * @param self
 * @parma env
 * @param cache
 * @param eh
 */
void il_factor_this_load(il_factor_this* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * thisで参照されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_this_eval(il_factor_this* self, struct enviroment* env, il_load_cache* cache);

/**
 * thisを表す要素を開放します.
 * @param self
 */
void il_factor_this_delete(il_factor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
