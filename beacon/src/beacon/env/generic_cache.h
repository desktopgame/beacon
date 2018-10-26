#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../util/vector.h"

struct GenericType;
struct type;
struct class_;
struct interface_;
struct Namespace;

/**
 * 型変数を含む型の宣言.
 */
typedef struct GenericCache {
	FQCNCache* FQCN;
	Vector* TypeArgs;
} GenericCache;

/**
 * 型変数を含む型宣言を作成します.
 * @return
 */
GenericCache* NewGenericCache();

/**
 * 型変数つきの型宣言をインデント無しで出力します.
 * @param self
 */
void PrintGenericCache(GenericCache* self);
/**
 * 型変数つきの型宣言をインデント付きで出力します.
 * @param self
 */
void DumpGenericCache(GenericCache* self, int depth);

/**
 * @param self
 * @return
 */
char* GenericCacheToString(GenericCache* self);

/**
 * 型変数つきの型宣言を解放します.
 * @param self
 */
void DeleteGenericCache(GenericCache* self);

/**
 * @param a
 * @param b
 * @return
 */
bool EqualsGenericCache(GenericCache* a, GenericCache* b);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H
