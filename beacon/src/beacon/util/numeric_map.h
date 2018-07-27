#ifndef BEACON_UTIL_NUMERIC_MAP_H
#define BEACON_UTIL_NUMERIC_MAP_H
typedef int numeric_key;
typedef void* numeric_map_item;

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

numeric_map* numeric_map_new();

numeric_map* numeric_map_put(numeric_map* self, numeric_key key, numeric_map_item item);

numeric_map* numeric_map_cell(numeric_map* self, numeric_key key);

numeric_map_item numeric_map_get(numeric_map* self, numeric_key key);

int numeric_map_compare(numeric_map* self, numeric_key key);

void numeric_map_each(numeric_map* self, numeric_tree_action a);

void numeric_map_delete(numeric_map* self, numeric_tree_element_deleter deleter);

void numeric_map_deleter_null(numeric_key name, numeric_map_item item);

void numeric_map_deleter_free(numeric_key name, numeric_map_item item);
#endif