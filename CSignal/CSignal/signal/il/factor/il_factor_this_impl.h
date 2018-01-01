#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_THIS_H
#define SIGNAL_IL_IL_FACTOR_THIS_H
struct enviroment;
struct class_;
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
 */
void il_factor_this_generate(il_factor_this* self, struct enviroment* env);

/**
 * thisで参照されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @return
 */
struct class_* il_factor_this_eval(il_factor_this* self, struct enviroment* env);

/**
 * thisを表す要素を開放します.
 * @param self
 */
void il_factor_this_delete(il_factor_this* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
