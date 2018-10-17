#pragma once
#ifndef BEACON_UTIL_StringBuffer_H
#define BEACON_UTIL_StringBuffer_H
#include <stdarg.h>

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct StringBuffer_t {
	int Length;
	int Capacity;
	char* Text;
} StringBuffer;

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
StringBuffer* MallocBuffer(const char* filename, int lineno);

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void AppendBuffer(StringBuffer* self, char c);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ...
 */
void AppendfBuffer(StringBuffer* self, const char* fmt, ...);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ap
 */
void VappendfBuffer(StringBuffer* self, const char* fmt, va_list ap);

/**
 * 全て追記します.
 * @param self
 * @param s
 */
void AppendsBuffer(StringBuffer* self, const char* s);

/**
 * shrink,freeを実行して文字列だけを返します.
 * @param self
 * @return
 */
char* ReleaseBuffer(StringBuffer* self);

/**
 * バッファを拡張します.
 * @param self
 */
void ReserveBuffer(StringBuffer* self);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void ShrinkBuffer(StringBuffer* self);

/**
 * @param self
 * @param lineIndex
 * @param len
 * @return
 */
StringBuffer* IndentBuffer(StringBuffer* self, int lineIndex, int len);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void DeleteBuffer(StringBuffer* self);
#endif // !SIGNAL_UTIL_StringBuffer_H
