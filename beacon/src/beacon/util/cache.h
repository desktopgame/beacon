#ifndef BEACON_UTIL_CACHE_H
#define BEACON_UTIL_CACHE_H
/**
 * 整数以外の任意の値を格納出来る連結リストです。
 */
typedef struct bc_Cache {
        void* Data;
        struct bc_Cache* Next;
} bc_Cache;

/**
 * ベクターのデリータ関数です.
 * @param item
 */
typedef void (*bc_CacheDataDeleter)(void* item);

/**
 * 指定の長さのキャッシュを作成します。
 * @param capacity
 * @return
 */
bc_Cache* bc_NewCache(int capacity);

/**
 * 空いている要素を検索して data をセットします。
 * 全て埋まっている場合はキャッシュを延長します。
 * @param self
 * @param data
 */
void bc_StoreCache(bc_Cache* self, void* data);

/**
 * キャッシュから要素を取り除きます。
 * @param self
 * @param data
 */
void bc_EraseCache(bc_Cache* self, void* data);

/**
 * 全てのキャッシュを削除します。
 * @param self
 * @param deleter
 */
void bc_DeleteCache(bc_Cache* self, bc_CacheDataDeleter deleter);

#endif