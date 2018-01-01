#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_SUPER_H
#define SIGNAL_IL_IL_FACTOR_SUPER_H
struct enviroment;
struct class_;

/**
 * superを表す要素.
 */
typedef int il_factor_super;

/**
 * superを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_super_dump(il_factor_super* self, int depth);

/**
 * superを表す要素を出力します.
 * @param self
 * @param env
 */
void il_factor_super_generate(il_factor_super* self, struct enviroment* env);

/**
 * superで参照されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @return
 */
struct class_* il_factor_super_eval(il_factor_super* self, struct enviroment* env);

/**
 * superを表す要素を出力します.
 * @param depth
 */
void il_factor_super_delete(il_factor_super* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
