#pragma once
#ifndef BEACON_UTIL_TEXT_H
#define BEACON_UTIL_TEXT_H
#include "vector.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "../util/io.h"

//clangでは errno_t が見つからない
#if defined(__clang__)
typedef int SG_errno_t;
#else
typedef errno_t SG_errno_t;
#endif

/**
 * 引数の文字列を複製して返します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param source
 */
char* text_strdup(const char* source);

/**
 * 1行読み込んで返します.
 * @return 呼び出し側で開放してください.
 */
char* text_gets();

/**
 * strが空白文字だけで構成されるなら true.
 * @param str
 * @return
 */
bool text_white(const char* str);

/**
 * 指定位置の文字を取り出します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param outChar
 * @param index 取り出す位置
 * @param source
 * @param dataSize 一文字のサイズ
 */
SG_errno_t text_strncpy(char* outChar, size_t index, const char* source, size_t dataSize);

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

/**
 * ソースにテキストが含まれるなら true.
 * @param source
 * @param text
 * @return
 */
bool text_contains(const char* source, const char* text);

/**
 * 標準入力から一行読み込んで返します.
 * @return
 */
char* text_readline();

/**
 * 指定のファイルから一行読み込みます.
 * @param fp
 * @return
 */
char* text_freadline(FILE* fp);
#endif // !SIGNAL_UTIL_TEXT_H
