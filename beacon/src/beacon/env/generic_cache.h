#pragma once
#ifndef BEACON_ENV_GENERIC_CACHE_H
#define BEACON_ENV_GENERIC_CACHE_H
#include "fqcn_cache.h"
#include "../il/il_context.h"
#include "../util/vector.h"

struct generic_type;
struct type;
struct class_;
struct interface_;
struct namespace_;

/**
 * 型変数を含む型の宣言.
 */
typedef struct generic_cache {
	fqcn_cache* fqcn;
	vector* type_args;
} generic_cache;

/**
 * 型変数を含む型宣言を作成します.
 * @return
 */
generic_cache* generic_cache_new();

/**
 * 型変数つきの型宣言をインデント無しで出力します.
 * @param self
 */
void generic_cache_print(generic_cache* self);
/**
 * 型変数つきの型宣言をインデント付きで出力します.
 * @param self
 */
void generic_cache_dump(generic_cache* self, int depth);

/**
 * @param self
 * @return
 */
char* generic_cache_tostr(generic_cache* self);

/**
 * 型変数つきの型宣言を解放します.
 * @param self
 */
void generic_cache_delete(generic_cache* self);
#endif // !SIGNAL_ENV_GENERIC_CACHE_H
