#pragma once
#ifndef SIGNAL_ENV_FQCN_CACHE_H
#define SIGNAL_ENV_FQCN_CACHE_H
#include "../util/vector.h"
struct namespace_;
/**
 * Full Quality Class Name を表す構造体.
 */
typedef struct fqcn_cache {
	vector* scope_vec;
	char* name;
} fqcn_cache;

/**
 * FQCNキャッシュを作成します.
 * @return
 */
fqcn_cache* fqcn_cache_new();

/**
 * FQCNキャッシュを出力します.
 * @param self
 * @param depth
 */
void fqcn_cache_dump(fqcn_cache* self, int depth);

/**
 * FQCNを切り詰めて改行せずに表示します.
 * @param self
 */
void fqcn_cache_print(fqcn_cache* self);

/**
 * FQCNが示す名前空間を返します.
 * X::Y ではなく、 Y の場合は NULL を返します。
 * @param self
 * @return
 */
struct namespace_* fqcn_scope(fqcn_cache* self);

/**
 * FQCNキャッシュを開放します.
 * @param self
 */
void fqcn_cache_delete(fqcn_cache* self);
#endif // !SIGNAL_ENV_FQCN_CACHE_H
