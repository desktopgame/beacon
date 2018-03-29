#pragma once
#ifndef BEACON_IL_IL_LOAD_CACHE_H
#define BEACON_IL_IL_LOAD_CACHE_H
#include "../util/vector.h"
#include <stdbool.h>

/**
 * ILを読み込むためのキャッシュです.
 */
typedef struct il_load_cache {
	vector* namespace_vec;
	vector* type_vec;
	vector* method_vec;
	vector* receiver_vec;
	vector* type_args_vec;
	vector* while_start_vec;
	vector* while_end_vec;
	bool toplevel;
} il_load_cache;

struct namespace_;
struct class_;
struct fqcn_cache;

/**
 * ILキャッシュを作成します.
 * @return
 */
il_load_cache* il_load_cache_new();

/**
 * 現在のスコープの名前空間を返します.
 * @param self
 * @return
 */
struct namespace_* il_load_cache_namespace(il_load_cache* self);

/**
 * 現在解析中のクラスを返します.
 * @param self
 * @return
 */
struct class_* il_load_cache_class(il_load_cache* self, struct fqcn_cache* fqcn);

/**
 * ILキャッシュを開放します
 * @param self
 */
void il_load_cache_delete(il_load_cache* self);
#endif // !SIGNAL_IL_IL_LOAD_CACHE_H
