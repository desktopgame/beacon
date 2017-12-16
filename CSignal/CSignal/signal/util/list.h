#pragma once
#ifndef SIGNAL_UTIL_LIST_H
#define SIGNAL_UTIL_LIST_H
/**
 * リストに格納するデータ型.
 */
typedef void* list_item;

/**
 * リスト.
 */
typedef struct list {
	list_item item;
	struct list* prev;
	struct list* next;
} list;

/**
 * リストのデリータ関数です.
 * @param item
 */
typedef void(*list_element_deleter)(list_item item);

/**
 * リストのアクション関数です.
 * @param item
 */
typedef void(*list_element_action)(list_item item);

/**
 * 新しいリストを作成します.
 * @return
 */
list* list_new(void);

/**
 * 末尾に要素を追加します.
 * @param self
 * @param item
 */
list_item list_add(list* self, list_item item);

/**
 * 指定位置の要素を返します.
 * @param self
 * @param index
 */
list_item list_at(list* self, int index);

/**
 * 全ての要素を訪問します.
 * @param self
 * @param action
 */
void list_foreach(list* self, list_element_action action);

/**
 * リストとその中身を開放します.
 * @param self
 * @param deleter
 */
void list_delete(list* self, list_element_deleter deleter);

/**
 * free によって解放するデリータです.
 * @param item
 */
void list_deleter_free(list_item item);

/**
 * 何も行わないデリータです.
 * @param item
 */
void list_deleter_null(list_item item);
#endif // !SIGNAL_UTIL_LIST_H
