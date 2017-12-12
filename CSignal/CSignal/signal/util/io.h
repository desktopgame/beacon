#pragma once
#ifndef SIGNAL_UTIL_IO_H
#define SIGNAL_UTIL_IO_H
#include <stdio.h>
#include <stdbool.h>

/**
 * 新しいファイルを作成します.
 * @param filename
 * @return
 */
void io_new_file(const char* filename);

/**
 * 指定のファイルが既に存在するなら true.
 * @param filename
 * @return
 */
bool io_exists(const char* filename);

/**
 * 指定のファイルを読み込んで返します.
 * @param filename
 * @return 呼び出し側で開放してください.
 */
char* io_read_text(const char* filename);

/**
 * 指定のファイルのテキストを上書きします.
 * @param filename
 * @param text
 * @return
 */
void io_write_text(const char* filename, const char* text);
#endif // !SIGNAL_UTIL_IO_H
