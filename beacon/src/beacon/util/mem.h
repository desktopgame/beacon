#pragma once
#ifndef BEACON_ENV_MEM_H
#define BEACON_ENV_MEM_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef unsigned char muchar_t;

#if defined(DEBUG)
/**
 * メモリリーク・オーバーランなどを検出するならこのマクロをオンにします.
 */
#define MEMORY_MANAGEMENT (1)

/**
 * 既に解放された領域へのアクセスを検出するならこのマクロをオンにします.
 */
//#define FREE_FREEZE (1)
#endif

#define MEM_MALLOC(size) (mem_malloc(size, __FILE__, __LINE__))
#define MEM_FREE(size) (mem_free(size, __FILE__, __LINE__))
#define MEM_REALLOC(block, size) (mem_realloc(block, size, __FILE__, __LINE__))
#define MEM_MARK(block, size) (mem_mark(block, size, __FILE__, __LINE__))
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
 * 現在確保中のすべてのメモリーをダンプします.
 */
void mem_dump();

/**
 * 指定の位置で確保されたメモリを監視します.
 * @param count
 */
void mem_break(int count);

/**
 * メモリ情報をトレースするためのキャッシュを開放します.
 */
void mem_destroy();

/**
 * @param fp
 * @param block
 * @param len
 * @return
 */
int mem_fprint(FILE* fp, void* block, int len);
#endif // !SIGNAL_ENV_MEM_H
