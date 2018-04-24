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
 * 型変数付きの型宣言を実際の generic_type へ変換します.
 * @param self
 * @param scope
 * @param ilctx
 * @return
 */
#define generic_cache_gtype(self, scope, ilctx) (generic_cache_gtypeloc(self, scope, ilctx, __FILE__, __LINE__))

/**
 * 型変数付きの型宣言を実際の generic_type へ変換します.
 * 通常はこちらではなくマクロ版の generic_cache_gtype を使用します。
 * @param self
 * @param scope
 * @param ilctx
 * @return
 */
struct generic_type* generic_cache_gtypeloc(generic_cache* self, struct namespace_* scope, il_context* ilctx, const char* filename, int lineno);

/**
 * generic_cache を typeへ変換します.
 * 型変数は無視されます。
 * @param self
 * @param scope
 * @return
 */
struct type* generic_cache_type(generic_cache* self, struct namespace_* scope);

/**
 * generic_cache を classへ変換します.
 * 型変数は無視されます。
 * @param self
 * @param scope
 * @return
 */
struct class_* generic_cache_class(generic_cache* self, struct namespace_* scope);
/**
 * generic_cache を interfaceへ変換します.
 * 型変数は無視されます。
 * @param self
 * @param scope
 * @return
 */
struct interface_* generic_cache_interface(generic_cache* self, struct namespace_* scope);

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
