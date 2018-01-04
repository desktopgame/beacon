#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_CHAR_H
#define SIGNAL_IL_IL_FACTOR_CHAR_H
#include "../il_factor_interface.h"
//struct opcode_buf;
/**
 * 文字を表す要素.
 */
typedef struct il_factor_char {
	char value;
} il_factor_char;

/**
 * 文字を表す要素をスーパーセットにラップします.
 * @param self
 */
il_factor* il_factor_wrap_char(il_factor_char* self);

/**
 * 文字を表す要素を作成します.
 * @param c
 * @return
 */
il_factor_char* il_factor_char_new(char c);

/**
 * 文字を表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_char_dump(il_factor_char* self, int depth);

/**
 * 文字を生成します.
 * @param self
 * @param env
 */
void il_factor_char_generate(il_factor_char* self, struct enviroment* env);

/**
 * 文字を表す要素を読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_factor_char_load(il_factor_char* self, struct enviroment* env, il_ehandler* eh);

/**
 * 文字を表す要素の型を返します.
 * @param self
 * @param env
 * @return
 */
struct class_* il_factor_char_eval(il_factor_char* self, struct enviroment* env);

/**
 * 文字を表す要素を開放します.
 * @param self
 */
void il_factor_char_delete(il_factor_char* self);
#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
