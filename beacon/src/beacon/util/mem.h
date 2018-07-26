#pragma once
#ifndef BEACON_ENV_MEM_H
#define BEACON_ENV_MEM_H
#include <stdlib.h>
#include <stdbool.h>

#if defined(DEBUG)
#define MEMORY_MANAGEMENT (1)
#endif

#if defined(MEMORY_MANAGEMENT)
	#define MEM_MALLOC(size) (mem_malloc(size, __FILE__, __LINE__))
	#define MEM_FREE(size) (mem_free(size, __FILE__, __LINE__))
	#define MEM_REALLOC(block, size) (mem_realloc(block, size, __FILE__, __LINE__))
	#define MEM_MARK(block, size) (mem_mark(block, size, __FILE__, __LINE__))
#else
	#define MEM_MALLOC(size) (malloc(size))
	#define MEM_FREE(size) free(size)
	#define MEM_REALLOC(block, size) (realloc(block, size))
	#define MEM_MARK(block, size) (void)(0)
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
 * 前回実行した時のデータを元に予想されるメモリリークのタイミングを監視します.
 * データが存在しない場合には何もしません。
 * @param filename
 */
void mem_read(const char* filename);

/**
 * このメソッドを呼び出した時点でわかっているメモリリークを出力します.
 * ユーザ向けの情報ではなく、#mem_read によって読み込み可能なフォーマットで出力します。
 * @param filename
 * @return
 */
void mem_write(const char* filename);

/**
 * mem_malloc以外の方法で確保されたメモリを
 * このモジュールが管理するメモリの一覧に加えます.
 * ここで追加されたメモリは mem_free で開放してください。
 * @param p
 * @param size
 * @param filename
 * @param lineno
 */
void mem_mark(void* p, size_t size, const char* filename, int lineno);

/**
 * 指定の位置で確保されたメモリを監視します.
 * @param count
 */
void mem_break(int count);

/**
 * メモリ情報をトレースするためのキャッシュを開放します.
 */
void mem_destroy();


#endif // !SIGNAL_ENV_MEM_H
