#pragma once
#ifndef SIGNAL_ENV_MEM_H
#define SIGNAL_ENV_MEM_H

#define MEM_MALLOC(size) mem_malloc(size, __FILE__, __LINE__)
#define MEM_FREE(size) mem_free(size, __FILE__, __LINE__)
#define MEM_REALLOC(block, size) mem_realloc(block, size, __FILE__, __LINE__);
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
 * realloc のラッパーです.
 * 通常はこちらではなくマクロ版を使用します。
 * @param block
 * @param newSize
 * @param finename
 * @param lineno
 * @return
 */
void* mem_realloc(void* block, size_t newSize, const char* filename, int lineno);

/**
 * free のラッパーです.
 * 通常はこちらではなくマクロ版を使用します。
 * @param block
 * @param filename
 * @param lineno
 */
void mem_free(void* block, const char* filename, int lineno);

/**
 * 割りあてカウントを +1 します.
 * strdup のようなメソッドを使用した後に呼び出します。
 */
void mem_inc();

/**
 * 割り当てカウントを -1 します.
 */
void mem_dec();

/**
 * プログラムの最後で呼び出します.
 */
void mem_check();
#endif // !SIGNAL_ENV_MEM_H
