#pragma once
#ifndef BEACON_UTIL_VECTOR_H
#define BEACON_UTIL_VECTOR_H
#include <stdlib.h>
#include <stdbool.h>

/**
 * ベクターの要素を表す型.
 */
typedef void* vector_item;

/**
 * 再帰を使用せずに実装された可変長配列です.
 * 0/NULLを格納することが出来ます。
 */
typedef struct vector {
	//使用されている長さ
	int length;
	//余分に確保された分も含めた長さ
	int capacity;
	//要素一つ分のサイズ
	//vector_slot_size_t slotSize;
	vector_item* memory;
} vector;

/**
 * vecの中の全ての要素を type へキャストして、 item へ代入しながら { ... } の内側を実行します.
 * type型で、itemを事前に宣言している必要があります。
 * <code>
 *	vector* v = vector_new();
 *	vector_push(v, 10);
 *	vector_push(v, 20);
 *	vector_push(v, 30);
 *	int item = 0;
 *	VFOREACH(index, int, item, v) {
 *		printf("hello %d %d \n", index, item);
 *	}
 * </code>
 * @param type
 * @param item
 * @param vec
 */
#define VFOREACH(vindex, type, item, vvec) \
	for(int vindex=0, item=(type)vector_at(vvec, vindex); \
		vindex<(vvec->length); \
		item=(type)vector_at(vvec, ++vindex) \
	) \

/**
 * ベクターのデリータ関数です.
 * @param item
 */
typedef void(*vector_element_deleter)(vector_item item);

typedef void(*vector_action)(vector_item item);

/**
 * ベクターを作成します.
 */
#define vector_new() (vector_malloc(__FILE__, __LINE__))

/**
 * ベクターを作成します.
 * @param filename
 * @param lineno
 */
vector* vector_malloc(const char* filename, int lineno);

/**
 * 末尾に要素を追加します.
 * @param self
 * @param item
 */
void vector_push(vector* self, vector_item item);

/**
 * selfが空なら新規作成して返します.
 * @param self
 * @param item
 * @return
 */
vector* vector_append(vector* self, vector_item item);

/**
 * 末尾の要素を削除せずに返します.
 * @param self
 * @return
 */
vector_item vector_top(vector* self);

/**
 * 末尾の要素を削除して返します.
 * @param self
 * @return
 */
vector_item vector_pop(vector* self);

/**
 * 指定位置に値を挿入します.
 * indexから末尾までの要素を一つ右にシフトします。
 * 次に index を item で上書きします。
 * @param self
 * @param index
 * @param item
 */
void vector_insert(vector* self, int index, vector_item item);

/**
 * 指定位置の要素を削除します.
 * @param self
 * @param index
 */
vector_item vector_remove(vector* self, int index);

/**
 * 容量を圧縮します.
 * @param self
 */
void vector_pack(vector* self);

/**
 * 容量を拡張します.
 * @param self
 * @return 新しいキャパシティサイズ
 */
int vector_reserve(vector* self);

/**
 * 指定位置の要素を上書きします.
 * 長さが足りない場合は 0 で伸ばします。
 * @param self
 * @param index
 * @param item
 */
void vector_assign(vector* self, int index, vector_item item);

/**
 * 指定位置の要素を返します.
 * @param self
 * @param index
 * @return
 */
vector_item vector_at(vector* self, int index);

/**
 * @param self
 * @param offset
 * @param len
 * @return
 */
vector* vector_sub(vector* self, int offset, int len);

/**
 * 空なら true.
 * @param self
 * @return
 */
bool vector_empty(vector* self);

/**
 * 先頭から検索して一致するものがあるなら添え字を返します.
 * @param self
 * @param item
 * @return 見つからなければ -1
 */
int vector_find(vector* self, vector_item item);

/** 
 * 先頭から検索して一致するものがあるなら true を返します.
 * @param self
 * @param item
 * @return 見つからなければ false
 */
bool vector_contains(vector* self, vector_item item);

/**
 * 中身を空にします.
 * @param self
 */
void vector_clear(vector* self);

/**
 * ベクターを開放します.
 * @param self
 * @param deleter
 */
void vector_delete(vector* self, vector_element_deleter deleter);

/**
 * free によって解放するデリータ.
 * @param item
 */
void vector_deleter_free(vector_item item);

/**
 * 何も行わないデリータ.
 * @param item
 */
void vector_deleter_null(vector_item item);

/**
 * @param source
 * @return
 */
vector* vector_clone(vector* source);

/**
 * srcからdestへコピーします.
 * @param src
 * @param dest
 */
void vector_copy(vector* src, vector* dst);

/**
 * @param self
 * @param a
 */
void vector_each(vector* self, vector_action a);

/**
 * @param src
 * @param dst
 */
void vector_merge(vector* src, vector* dst);
#endif // !SIGNAL_UTIL_VECTOR_H
