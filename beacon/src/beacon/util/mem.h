#pragma once
#ifndef BEACON_ENV_MEM_H
#define BEACON_ENV_MEM_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#if defined(_MSC_VER)
#include <crtdbg.h>
#endif

typedef unsigned char muchar_t;
#if defined(_MSC_VER)
	#if defined(_DEBUG)
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (_malloc_dbg(size,_NORMAL_BLOCK,__FILE__,__LINE__))
		#define MEM_FREE(size) (_free_dbg(size, _NORMAL_BLOCK))
		#define MEM_REALLOC(block, size) (_realloc_dbg(block, size, _NORMAL_BLOCK, __FILE__, __LINE__))
		#define MEM_MARK(block, size) ((void)0)
	#else
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (malloc(size))
		#define MEM_FREE(size) (free(size))
		#define MEM_REALLOC(block, size) (realloc(block, size))
		#define MEM_MARK(block, size) ((void)0)
	#endif
#else
	#if defined(DEBUG)
		/**
		 * メモリリーク・オーバーランなどを検出するならこのマクロをオンにします.
		 */
		#define MEMORY_MANAGEMENT (1)

		/**
		 * 簡易的なメモリ検査のみを実行します.
		 */
		//#define FAST_DIAGNOSTIC (1)

		#if defined(MEMORY_MANAGEMENT) && defined(FAST_DIAGNOSTIC)
		"error"
		#endif

		/**
		 * 既に解放された領域へのアクセスを検出するならこのマクロをオンにします.
		 */
		//#define FREE_FREEZE (1)

		#define NON_NULL(m) (mem_non_null(m))

		#define MEM_MALLOC(size) (mem_malloc(size, __FILE__, __LINE__))
		#define MEM_FREE(size) (mem_free(size, __FILE__, __LINE__))
		#define MEM_REALLOC(block, size) (mem_realloc(block, size, __FILE__, __LINE__))
		#define MEM_MARK(block, size) (mem_mark(block, size, __FILE__, __LINE__))
	#else
		#define NON_NULL(m) (m)
		#define MEM_MALLOC(size) (malloc(size))
		#define MEM_FREE(size) (free(size))
		#define MEM_REALLOC(block, size) (realloc(block, size))
		#define MEM_MARK(block, size) ((void)0)
	#endif
#endif
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

/**
 * m が NULL出なければプログラムを終了します.
 * @param m
 * @return
 */
void* mem_non_null(void* m);
#endif // !SIGNAL_ENV_MEM_H
