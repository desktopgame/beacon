#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_CHAR_H
#define SIGNAL_IL_IL_FACTOR_CHAR_H
/**
 * 文字を表す要素.
 */
typedef struct il_factor_char {
	char value;
} il_factor_char;

/**
 * 文字を表す要素を作成します.
 * @param c
 * @return
 */
il_factor_char* il_factor_char_new(char c);

/**
 * 文字を表す要素を開放します.
 * @param self
 */
void il_factor_char_delete(il_factor_char* self);
#endif // !SIGNAL_IL_IL_FACTOR_CHAR_H
