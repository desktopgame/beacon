#pragma once
#ifndef SIGNAL_UTIL_TEXT_H
#define SIGNAL_UTIL_TEXT_H

/**
 * 改行文字を出力します
 */
void text_putline(void);

/**
 * 指定の数だけ空白を出力します.
 * @param depth
 */
void text_putindent(int depth);

/**
 * 引数の文字列を複製して返します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param source
 */
char* text_strdup(const char* source);

/**
 * 二つの文字列を連結して返します.
 * @param a
 * @param b
 * @return 呼び出し側で開放してください.
 */
char* text_concat(const char* a, const char* b);
#endif // !SIGNAL_UTIL_TEXT_H
