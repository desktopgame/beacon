#pragma once
#ifndef SIGNAL_UTIL_TEXT_H
#define SIGNAL_UTIL_TEXT_H
#include "vector.h"

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
 * 指定位置の文字を取り出します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param outChar
 * @param index 取り出す位置
 * @param source
 * @param dataSize 一文字のサイズ
 */
errno_t text_strncpy(char* outChar, size_t index, const char* source, size_t dataSize);

/**
 * 二つの文字列を連結して返します.
 * @param a 呼び出し側で開放してください.
 * @param b 呼び出し側で開放してください.
 * @return 呼び出し側で開放してください.
 */
char* text_concat(const char* a, const char* b);

/**
 * 指定の位置の行を取り出します.
 * @param src
 * @param lineno
 * @return 呼び出し側で開放してください。
 */
char* text_lineat(const char* src, int lineno);

/**
 * v の中の文字列を全て連結します.
 * @param v 呼び出し側で開放してください.
 * @return 呼び出し側で開放してください.
 */
char* text_sum(vector* v, char* join);
#endif // !SIGNAL_UTIL_TEXT_H
