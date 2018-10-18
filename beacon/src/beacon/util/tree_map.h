#pragma once
#ifndef BEACON_UTIL_TREE_MAP_H
#define BEACON_UTIL_TREE_MAP_H
/**
 * ツリーマップに格納可能なキーの型.
 */
typedef const char* TreeKey;

/**
 * ツリーマップに格納可能な値の型.
 */
typedef void* TreeItem;

/** 
 * キーと値を紐づけて管理するマップ.
 */
typedef struct TreeMap {
	char* Key;
	TreeItem Item;
	//struct TreeMap* parent;
	struct TreeMap* Parent;
	struct TreeMap* Left;
	struct TreeMap* Right;
} TreeMap;


/**
 * ツリーのアクション関数です.
 * @param item
 */
typedef void(*tree_action)(const char* name, TreeItem item);

/**
 * ツリーのデリータ関数です.
 * @param item
 */
typedef void(*tree_element_deleter)(const char* name, TreeItem item);

/**
 * 新しいツリーマップを作成します.
 * @return
 */
TreeMap* NewTreeMap();

/**
 * 指定のツリーマップで指定のキーと値を紐づけます.
 * @param self
 * @param key
 * @param item
 */
TreeMap* PutTreeMap(TreeMap* self, TreeKey key, TreeItem item);

/**
 * 指定のツリーマップで指定のキーに紐づけられた値を返します.
 * @param self
 * @param key
 * @return
 */
TreeItem GetTreeMapValue(TreeMap* self, TreeKey key);

/**
 * 要素を格納しているセルを返します.
 * @param self
 * @param key
 * @return
 */
TreeMap* GetTreeMapCell(TreeMap* self, TreeKey key);

/**
 * ツリーのキーと引数のキーを比較します.
 * @param self
 * @param key
 * @return
 */
int CompareTreeMap(TreeMap* self, TreeKey key);

/**
 * ツリー内のすべての要素を訪問します.
 * @param self
 * @param act
 */
void EachTreeMap(TreeMap* self, tree_action act);

/**
 * ツリーと全ての要素を削除します.
 * @param self
 * @param deleter
 */
void DeleteTreeMap(TreeMap* self, tree_element_deleter deleter);

/**
 * freeによって解放するデリータの実装です.
 * @param item
 */
void TreeMapDeleterByFree(const char* key, TreeItem item);

/**
 * 何も行わないデリータの実装です.
 * @param item
 */
void TreeMapDeleterOfNull(const char* key, TreeItem item);
#endif // !SIGNAL_UTIL_TREE_MAP_H
