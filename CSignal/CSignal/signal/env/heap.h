#pragma once
#ifndef SIGNAL_ENV_HEAP_H
#define SIGNAL_ENV_HEAP_H
#include "../util/vector.h"
#include "object.h"

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct heap {
	int threshold;
	vector* object_vec;
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
 * ヒープを開放します.
 * @param self
 */
void heap_delete(heap* self);
#endif // !SIGNAL_ENV_HEAP_H
