#pragma once
#ifndef SIGNAL_UTIL_IO_H
#define SIGNAL_UTIL_IO_H
#include <stdio.h>

/**
 * 新しいファイルを作成します.
 * @param filename
 * @return
 */
void io_new_file(const char* filename);

/**
 * 指定のファイルを読み込んで返します.
 * @param filename
 * @return
 */
char* io_read_text(const char* filename);
#endif // !SIGNAL_UTIL_IO_H
