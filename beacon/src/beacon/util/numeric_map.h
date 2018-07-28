#ifndef BEACON_UTIL_NUMERIC_MAP_H
#define BEACON_UTIL_NUMERIC_MAP_H
typedef int numeric_key;
typedef void* numeric_map_item;
/**
 * 整数をキーとして二分探索を行うマップ.
 */
typedef struct numeric_map {
	numeric_key key;
	numeric_map_item item;
	struct numeric_map* parent;
	struct numeric_map* left;
	struct numeric_map* right;
} numeric_map;
/**
 * ツリーのアクション関数です.
 * @param item
 */
typedef void(*numeric_tree_action)(numeric_key name, numeric_map_item item);

/**
 * ツリーのデリータ関数です.
 * @param item
 */
typedef void(*numeric_tree_element_deleter)(numeric_key name, numeric_map_item item);

/**
 * 新しいヌメリックマップを作成します.
 * @return
 */
numeric_map* numeric_map_new();

/**
 * 指定のキーと値を紐付けます.
 * @param self
 * @param key
 * @param item
 * @return
 */
numeric_map* numeric_map_put(numeric_map* self, numeric_key key, numeric_map_item item);

/**
 * 指定のキーに紐づけられたセルを返します.
 * @param self
 * @param key
 */
numeric_map* numeric_map_cell(numeric_map* self, numeric_key key);

/**
 * 指定のキーに紐づけられた値を返します.
 * @param self
 * @param key
 * @return
 */
numeric_map_item numeric_map_get(numeric_map* self, numeric_key key);

/**
 * 指定のキーと比較します.
 * @param self
 * @param key
 * @return
 */
int numeric_map_compare(numeric_map* self, numeric_key key);

/**
 * マップの全ての要素を訪問します.
 * @param self
 * @param a
 */
void numeric_map_each(numeric_map* self, numeric_tree_action a);

/**
 * マップを解放します.
 * @param self
 * @param deleter
 */
void numeric_map_delete(numeric_map* self, numeric_tree_element_deleter deleter);

/**
 * 何も行わないデリータ.
 * @param name
 * @param item
 */
void numeric_map_deleter_null(numeric_key name, numeric_map_item item);

/**
 * free によって解放するデリータ.
 * @param name
 * @param item
 */
void numeric_map_deleter_free(numeric_key name, numeric_map_item item);
#endif