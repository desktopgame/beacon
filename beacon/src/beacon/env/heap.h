#pragma once
#ifndef BEACON_ENV_HEAP_H
#define BEACON_ENV_HEAP_H
#include "../util/vector.h"
#include "object.h"
#include <stdbool.h>

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct heap {
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
 * 追加せずに obj#paint を paint_onexit_T へ変更します。
 * @param self
 * @param obj
 */
void heap_add(heap* self, object* obj);

/**
 * GCを実行します.
 * @param self
 */
void heap_gc(heap* self);

/**
 * 指定のオブジェクトをヒープから取り除きます.
 * @param self
 * @param o
 */
void heap_ignore(heap* self, object* o);

/**
 * ヒープを開放します.
 * @param self
 */
void heap_delete(heap* self);

/**
 * ヒープの中身をダンプします.
 * @param self
 */
void heap_dump(heap* self);
#endif // !SIGNAL_ENV_HEAP_H
