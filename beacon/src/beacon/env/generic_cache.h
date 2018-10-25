#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../util/vector.h"

struct generic_type;
struct type;
struct class_;
struct interface_;
struct Namespace;

/**
 * 型変数を含む型の宣言.
 */
typedef struct generic_cache {
	FQCNCache* fqcn;
	Vector* type_args;
} generic_cache;

/**
 * 型変数を含む型宣言を作成します.
 * @return
 */
generic_cache* NewGenericCache();

/**
 * 型変数つきの型宣言をインデント無しで出力します.
 * @param self
 */
void PrintGenericCache(generic_cache* self);
/**
 * 型変数つきの型宣言をインデント付きで出力します.
 * @param self
 */
void DumpGenericCache(generic_cache* self, int depth);

/**
 * @param self
 * @return
 */
char* GenericCacheToString(generic_cache* self);

/**
 * 型変数つきの型宣言を解放します.
 * @param self
 */
void DeleteGenericCache(generic_cache* self);

/**
 * @param a
 * @param b
 * @return
 */
bool EqualsGenericCache(generic_cache* a, generic_cache* b);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H
