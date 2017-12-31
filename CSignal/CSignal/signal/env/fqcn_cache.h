#pragma once
#ifndef SIGNAL_ENV_FQCN_CACHE_H
#define SIGNAL_ENV_FQCN_CACHE_H
#include "../util/vector.h"

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
 * FQCNキャッシュを開放します.
 * @param self
 */
void fqcn_cache_delete(fqcn_cache* self);
#endif // !SIGNAL_ENV_FQCN_CACHE_H
