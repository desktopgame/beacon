#pragma once
#ifndef SIGNAL_IL_IL_LOAD_CACHE_H
#define SIGNAL_IL_IL_LOAD_CACHE_H
#include "../util/vector.h"
#include <stdbool.h>

/**
 * ILを読み込むためのキャッシュです.
 */
typedef struct il_load_cache {
	vector* namespace_vec;
	vector* type_vec;
	vector* while_start_vec;
	vector* while_end_vec;
	bool toplevel;
} il_load_cache;

/**
 * ILキャッシュを作成します.
 * @return
 */
il_load_cache* il_load_cache_new();

/**
 * ILキャッシュを開放します
 * @param self
 */
void il_load_cache_delete(il_load_cache* self);
#endif // !SIGNAL_IL_IL_LOAD_CACHE_H
