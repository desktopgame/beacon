#pragma once
#ifndef SIGNAL_UTIL_TEXT_H
#define SIGNAL_UTIL_TEXT_H

/**
 * 改行文字を出力します
 */
void text_putline(void);

/**
 * 引数の文字列を複製して返します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param source
 */
char* text_strdup(const char* source);
#endif // !SIGNAL_UTIL_TEXT_H
