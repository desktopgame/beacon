#pragma once
#ifndef SIGNAL_UTIL_STRING_BUFFER_H
#define SIGNAL_UTIL_STRING_BUFFER_H

/**
 * 格納される文字の型.
 */
typedef char char_t;

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct string_buffer {
	int length;
	int capacity;
	char_t* text;
} string_buffer;

/**
 * 文字列バッファーを作成します.
 * @return
 */
string_buffer* string_buffer_new();

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void string_buffer_append(string_buffer* self, char_t c);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void string_buffer_shrink(string_buffer* self);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void string_buffer_delete(string_buffer* self);
#endif // !SIGNAL_UTIL_STRING_BUFFER_H
