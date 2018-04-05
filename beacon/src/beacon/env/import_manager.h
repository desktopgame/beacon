#pragma once
#ifndef BEACON_ENV_IMPORT_MANAGER_H
#define BEACON_ENV_IMPORT_MANAGER_H
#include "../util/vector.h"
#include "virtual_type.h"
//#include "fqcn_cache.h"
struct generic_cache;
struct generic_type;
struct namespace_;
struct class_loader;
struct import_info;
struct il_context;

/**
 * あるファイルが参照しているファイルの一覧を管理します.
 */
typedef struct import_manager {
	vector* info_vec;
} import_manager;

/**
 * インポートマネージャを作成します.
 * @return
 */
import_manager* import_manager_new();

/**
 * 指定のクラスローダをインポートの一覧に含めます.
 * @param self
 * @param target
 * @return
 */
struct import_info* import_manager_import(import_manager* self, struct class_loader* target);

/**
 * 既に読み込まれたなら true.
 * @param self
 * @param index
 * @return
 */
bool import_manager_loaded(import_manager* self, int index);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param scope
 * @param fqcn
 * @return 解決出来なかったなら NULL を返します.
 */
void import_manager_resolve(import_manager* self, struct namespace_* scope, struct generic_cache* fqcn, struct il_context* ilcache, virtual_type* dest);

/**
 * インポートマネージャを開放します.
 * @param self
 */
void import_manager_delete(import_manager* self);
#endif // !SIGNAL_ENV_IMPORT_MANAGER_H
