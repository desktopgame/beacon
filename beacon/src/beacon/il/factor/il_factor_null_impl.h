#pragma once
#ifndef BEACON_IL_IL_FACTOR_NULL_H
#define BEACON_IL_IL_FACTOR_NULL_H
#include "../il_factor_interface.h"

struct enviroment;
struct type;

/**
 * nullをダンプします.
 * @param empty
 * @param depth
 */
void il_factor_null_dump(void* empty, int depth);

/**
 * nullを出力します.
 * @param empty
 * @param env
 * @param ilctx
 */
void il_factor_null_generate(void* empty, struct enviroment* env, il_context* ilctx);

/**
 * nullを読み込みます.
 * @param empty
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_null_load(void* empty, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * nullを表す型を返します.
 * @param empty
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_null_eval(void* empty, struct enviroment* env, il_context* ilctx);

#endif // !SIGNAL_IL_IL_FACTOR_NULL_H
