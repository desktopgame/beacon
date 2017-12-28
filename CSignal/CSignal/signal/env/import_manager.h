#pragma once
#ifndef SIGNAL_ENV_IMPORT_MANAGER_H
#define SIGNAL_ENV_IMPORT_MANAGER_H
#include "../util/vector.h"
struct class_;
struct class_loader;

/**
 * あるファイルが参照しているファイルの一覧を管理します.
 */
typedef struct import_manager {
	vector* class_loader_list;
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
 */
void import_manager_import(import_manager* self, struct class_loader* target);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param name
 * @return 解決出来なかったなら NULL を返します.
 */
struct class_* import_manager_resolve(import_manager* self, const char* name);

/**
 * インポートマネージャを開放します.
 * @param self
 */
void import_manager_delete(import_manager* self);
#endif // !SIGNAL_ENV_IMPORT_MANAGER_H
