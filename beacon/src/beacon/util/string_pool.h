#ifndef BEACON_UTIL_STRINGPOOL_H
#define BEACON_UTIL_STRINGPOOL_H
#include <stdio.h>

struct string_buffer;

//NULL
#define NULL_VIEW (0)

//""
#define ZERO_VIEW (1)

/**
 * 符号化された文字列.
 */
typedef unsigned int string_view;

/**
 * 文字列プールを初期化します.
 */
void string_pool_init();

/**
 * 文字列を符号化してその参照を返します.
 * @param str
 * @return
 */
string_view string_pool_intern(const char* str);

/**
 * 引数の文字列を符号化して返します.
 * @param buffer
 * @return
 */
string_view string_pool_intern2(struct string_buffer* buffer);

/**
 * 文字列が既に符号化されているならそれを返します.
 * @param str
 * @return
 */
string_view string_pool_str2ref(const char* str);

/**
 * 参照からソース文字列を返します.
 * @param ref
 * @return
 */
const char* string_pool_ref2str(string_view ref);

/**
 * プールに格納された全ての文字列を出力します.
 * @param fp
 */
void string_pool_dump(FILE* fp);

/**
 * 文字列プールを解放します.
 */
void string_pool_destroy();
#endif