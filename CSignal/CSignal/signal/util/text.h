#pragma once
#ifndef SIGNAL_UTIL_TEXT_H
#define SIGNAL_UTIL_TEXT_H
#include "vector.h"
#include <stdarg.h>
#include <stdbool.h>

//clangでは errno_t が見つからない
#if defined(__clang__)
typedef int SG_errno_t;
#else
typedef errno_t SG_errno_t;
#endif
/**
 * text_printf を介する出力をファイルへトレースするなら true.
 * @param b
 */
void text_set_trace(bool b);

/**
 * トレース中なら true.
 * @return
 */
bool text_is_trace();

/**
 * トレース中なら、現在バッファされている文字を
 * ファイルへフラッシュします.
 * この関数は main の最後で呼び出します。
 */
void text_flush_trace();

/**
 * 改行文字を出力します
 */
void text_putline(void);

/**
 * 真偽値型の値を出力します.
 * @param b
 */
void text_putb(bool b);

/**
 * printfへの委譲です.
 * @param message
 * @param ...
 * @return
 */
int text_printf(const char* message, ...);

/**
 * sprintfへの委譲です.
 * @param block
 * @param blockSize
 * @param message
 * @param ...
 * @return
 */
int text_sprintf(char* block, size_t blockSize, char* message, ...);
/**
 * sprintfへの委譲です.
 * @param block
 * @param blockSize
 * @param message
 * @param ...
 * @return
 */
int text_vsprintf(char* block, size_t blockSize, char* message, va_list ap);

/**
 * text_printf へ委譲したあと、
 * 改行を出力します。
 */
void text_printfln(const char* message, ...);

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
 * 1行読み込んで返します.
 * @return 呼び出し側で開放してください.
 */
char* text_gets();

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
#endif // !SIGNAL_UTIL_TEXT_H
