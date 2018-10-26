#pragma once
#ifndef BEACON_ENV_HEAP_H
#define BEACON_ENV_HEAP_H
#include "../util/vector.h"
#include "object.h"
#include <stdbool.h>

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct Heap {
	Vector* Objects;
	//この値が 1以上 なら、新しく確保されたオブジェクトは
	//ヒープに関連づけられません。
	//つまり、オブジェクトを自分で解放する必要があります。
	//これはリテラルのための機構です。
	int AcceptBlocking;
	//この値が 1以上 なら、新しくオブジェクトを確保した時に
	//オブジェクトの総数が閾値を上回っていてもGCを施工しません。
	int CollectBlocking;
} Heap;

/**
 * ヒープを作成します.
 * @return
 */
Heap* NewHeap();

/**
 * 現在のスクリプトコンテキストでヒープを返します.
 * @return
 */
Heap* GetHeap();

/**
 * ヒープにオブジェクトを追加します.
 * obj#blockingがtrueなら、
 * 追加せずに obj#paint を PAINT_ONEXIT_T へ変更します。
 * @param self
 * @param obj
 */
void AddHeap(Heap* self, Object* obj);

/**
 * GCを実行します.
 * @param self
 */
void CollectHeap(Heap* self);

/**
 * 指定のオブジェクトをヒープから取り除きます.
 * @param self
 * @param o
 */
void IgnoreHeap(Heap* self, Object* o);

/**
 * ヒープを開放します.
 * @param self
 */
void DeleteHeap(Heap* self);

/**
 * ヒープの中身をダンプします.
 * @param self
 */
void DumpHeap(Heap* self);
#endif // !SIGNAL_ENV_HEAP_H
