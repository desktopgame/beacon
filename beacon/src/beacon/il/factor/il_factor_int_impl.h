#pragma once
#ifndef BEACON_IL_IL_FACTOR_INT_H
#define BEACON_IL_IL_FACTOR_INT_H
#include "../il_factor_interface.h"
#include <stdint.h>
//struct opcode_buf;
#define IL_FACT2INT(fact) (il_factor_cast_int(fact))
/**
 * 整数リテラルを表す要素.
 */
typedef struct il_factor_int {
	int32_t value;
} il_factor_int;

/**
 * 整数リテラルをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_int(il_factor_int* self);

/**
 * 整数リテラルを表す要素を作成します.
 * @param i
 * @return
 */
il_factor_int* il_factor_int_new(int32_t i);

/**
 * 整数リテラルを出力します.
 * @param self
 * @param depth
 */
void il_factor_int_dump(il_factor_int* self, int depth);

/** 
 * 整数リテラルを生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_int_generate(il_factor_int* self, struct enviroment* env, il_load_cache* cache);

/**
 * 整数リテラルを読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_int_load(il_factor_int* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * 整数リテラルを表す要素の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_int_eval(il_factor_int* self, struct enviroment* env, il_load_cache* cache);

/**
 * 整数リテラルを表す要素を開放します.
 * @param self
 */
void il_factor_int_delete(il_factor_int* self);

il_factor_int* il_factor_cast_int(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_INT_H
