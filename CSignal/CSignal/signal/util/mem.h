#pragma once
#ifndef SIGNAL_ENV_MEM_H
#define SIGNAL_ENV_MEM_H

#define MEM_MALLOC(size) mem_malloc(size, __FILE__, __LINE__)
#define MEM_FREE(size) mem_free(size, __FILE__, __LINE__)

/**
 * malloc のラッパーです.
 * 通常はこちらではなくマクロ版を使用します。
 * @param size
 * @param filename
 * @param lineno
 * @return
 */
void* mem_malloc(size_t size, const char* filename, int lineno);

/**
 * free のラッパーです.
 * 通常はこちらではなくマクロ版を使用します。
 * @param block
 * @param filename
 * @param lineno
 */
void mem_free(void* block, const char* filename, int lineno);

/**
 * プログラムの最後で呼び出します.
 */
void mem_check();
#endif // !SIGNAL_ENV_MEM_H
