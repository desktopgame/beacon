#pragma once
#ifndef BEACON_UTIL_STRING_BUFFER_H
#define BEACON_UTIL_STRING_BUFFER_H
#include <stdarg.h>

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct string_buffer {
	int length;
	int capacity;
	char* text;
} string_buffer;

/**
 * 文字列バッファーを作成します.
 * @return
 */
#define NewBuffer() (MallocBuffer(__FILE__, __LINE__))

/**
 * 文字列バッファーを作成します.
 * @param filename
 * @param lineno
 * @return
 */
string_buffer* MallocBuffer(const char* filename, int lineno);

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void AppendBuffer(string_buffer* self, char c);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ...
 */
void AppendfBuffer(string_buffer* self, const char* fmt, ...);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ap
 */
void VappendfBuffer(string_buffer* self, const char* fmt, va_list ap);

/**
 * 全て追記します.
 * @param self
 * @param s
 */
void AppendsBuffer(string_buffer* self, const char* s);

/**
 * shrink,freeを実行して文字列だけを返します.
 * @param self
 * @return
 */
char* ReleaseBuffer(string_buffer* self);

/**
 * バッファを拡張します.
 * @param self
 */
void ReserveBuffer(string_buffer* self);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void ShrinkBuffer(string_buffer* self);

/**
 * @param self
 * @param lineIndex
 * @param len
 * @return
 */
string_buffer* IndentBuffer(string_buffer* self, int lineIndex, int len);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void DeleteBuffer(string_buffer* self);
#endif // !SIGNAL_UTIL_STRING_BUFFER_H
