#pragma once
#ifndef BEACON_IL_IL_FACTOR_DOUBLE_H
#define BEACON_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"
#define IL_FACT2DOUBLE(fact) (il_factor_cast_double(fact))
//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct il_factor_double {
	double value;
} il_factor_double;

/**
 * 浮動小数リテラルをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_double(il_factor_double* self);

/**
 * 浮動小数リテラルを表す要素を作成します.
 * @param d
 * @return
 */
il_factor_double* il_factor_double_new(double d);

/**
 * 浮動小数リテラルを表示します.
 * @param self
 * @param depth
 */
void il_factor_double_dump(il_factor_double* self, int depth);

/**
 * 浮動小数リテラルを表す要素を生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_double_generate(il_factor_double* self, struct enviroment* env, il_context* ilctx);

/**
 * 浮動小数リテラルを表す要素を作成します.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_double_load(il_factor_double* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * 浮動小数リテラルを表す要素の型を返します.
 * @param self
 * @param env
 * @param cache
 */
generic_type* il_factor_double_eval(il_factor_double* self, struct enviroment* env, il_context* ilctx);

/**
 * 浮動小数リテラルを表す要素を開放します.
 * @param self
 */
void il_factor_double_delete(il_factor_double* self);

il_factor_double* il_factor_cast_double(il_factor* fact);
#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
