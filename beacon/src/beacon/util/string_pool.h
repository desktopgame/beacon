#ifndef BEACON_UTIL_STRINGPOOL_H
#define BEACON_UTIL_STRINGPOOL_H
#include <stdio.h>
#include "string_buffer.h"

/**
 * NULL に対応する string_view です.
 */
#define NULL_VIEW (0)

/**
 * 空文字に対応する string_view です.
 */
#define ZERO_VIEW (1)

/**
 * 符号化された文字列.
 */
typedef unsigned int string_view;

/**
 * 文字列プールを初期化します.
 */
void InitStringPool();

/**
 * 文字列を符号化してその参照を返します.
 * @param str
 * @return
 */
string_view InternString(const char* str);

/**
 * 引数の文字列を符号化して返します.
 * @param buffer
 * @return
 */
string_view InternString2(Buffer* buffer);

/**
 * 二つの文字列を連結してインターンします.
 * @param head
 * @param foot
 * @return
 */
string_view ConcatIntern(const char* head, string_view foot);

/**
 * 文字列が既に符号化されているならそれを返します.
 * @param str
 * @return
 */
string_view Str2Ref(const char* str);

/**
 * 参照からソース文字列を返します.
 * @param ref
 * @return
 */
const char* Ref2Str(string_view ref);

/**
 * プールに格納された全ての文字列を出力します.
 * @param fp
 */
void DumpStringPool(FILE* fp);

/**
 * 文字列プールを解放します.
 */
void DestroyStringPool();
#endif