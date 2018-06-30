#pragma once
#ifndef BEACON_ENV_HEAP_H
#define BEACON_ENV_HEAP_H
#include "../util/vector.h"
#include "object.h"
#include <stdbool.h>

/**
 * GCの実行モード.
 */
typedef enum gc_mode {
	gc_full,
	gc_mini,
} gc_mode;

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct heap {
	int threshold;
	vector* object_vec;
	//この値が 1以上 なら、新しく確保されたオブジェクトは
	//ヒープに関連づけられません。
	//つまり、オブジェクトを自分で解放する必要があります。
	//これはリテラルのための機構です。
	int accept_blocking;
	//この値が 1以上 なら、新しくオブジェクトを確保した時に
	//オブジェクトの総数が閾値を上回っていてもGCを施工しません。
	int collect_blocking;
} heap;

/**
 * ヒープを作成します.
 * @return
 */
heap* heap_new();

/**
 * 現在のスクリプトコンテキストでヒープを返します.
 * @return
 */
heap* heap_get();

/**
 * ヒープにオブジェクトを追加します.
 * obj#blockingがtrueなら、
 * 追加せずに obj#paint を paint_onexit へ変更します。
 * @param self
 * @param obj
 */
void heap_add(heap* self, object* obj);

/**
 * GCを実行します.
 * @param self
 * @param mode
 */
void heap_gc(heap* self, gc_mode mode);

/**
 * ヒープを開放します.
 * @param self
 */
void heap_delete(heap* self);
#endif // !SIGNAL_ENV_HEAP_H
