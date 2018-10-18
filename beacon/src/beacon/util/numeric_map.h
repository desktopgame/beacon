#ifndef BEACON_UTIL_NUMERIC_MAP_H
#define BEACON_UTIL_NUMERIC_MAP_H
typedef int NumericMapKey;
typedef void* NumericMapItem;
/**
 * 整数をキーとして二分探索を行うマップ.
 */
typedef struct NumericMap {
	NumericMapKey Key;
	NumericMapItem Item;
	struct NumericMap* Parent;
	struct NumericMap* Left;
	struct NumericMap* Right;
} NumericMap;
/**
 * ツリーのアクション関数です.
 * @param item
 */
typedef void(*NumericMapAction)(NumericMapKey name, NumericMapItem item);

/**
 * ツリーのデリータ関数です.
 * @param item
 */
typedef void(*NumericMapDeleter)(NumericMapKey name, NumericMapItem item);

/**
 * 新しいヌメリックマップを作成します.
 * @return
 */
NumericMap* NewNumericMap();

/**
 * 指定のキーと値を紐付けます.
 * @param self
 * @param key
 * @param item
 * @return
 */
NumericMap* PutNumericMap(NumericMap* self, NumericMapKey key, NumericMapItem item);

/**
 * 指定のキーに紐づけられたセルを返します.
 * @param self
 * @param key
 */
NumericMap* GetNumericMapCell(NumericMap* self, NumericMapKey key);

/**
 * 指定のキーに紐づけられた値を返します.
 * @param self
 * @param key
 * @return
 */
NumericMapItem GetNumericMapValue(NumericMap* self, NumericMapKey key);

/**
 * 指定のキーと比較します.
 * @param self
 * @param key
 * @return
 */
int CompareNumericMap(NumericMap* self, NumericMapKey key);

/**
 * マップの全ての要素を訪問します.
 * @param self
 * @param a
 */
void EachNumericMap(NumericMap* self, NumericMapAction a);

/**
 * マップを解放します.
 * @param self
 * @param deleter
 */
void DeleteNumericMap(NumericMap* self, NumericMapDeleter deleter);

/**
 * 何も行わないデリータ.
 * @param name
 * @param item
 */
void NumericMapDeleterOfNull(NumericMapKey name, NumericMapItem item);

/**
 * free によって解放するデリータ.
 * @param name
 * @param item
 */
void NumericMapDeleterByFree(NumericMapKey name, NumericMapItem item);
#endif