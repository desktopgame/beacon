#pragma once
#ifndef BEACON_ENV_IMPORT_MANAGER_H
#define BEACON_ENV_IMPORT_MANAGER_H
#include "../util/vector.h"
//#include "virtual_type.h"
//#include "fqcn_cache.h"
struct generic_cache;
struct generic_type;
struct fqcn_cache;
struct namespace_;
struct class_loader;
struct ImportInfo;
struct CallContext;

/**
 * あるファイルが参照しているファイルの一覧を管理します.
 */
typedef struct import_manager {
	Vector* info_vec;
} import_manager;

/**
 * インポートマネージャを作成します.
 * @return
 */
import_manager* NewImportManager();

/**
 * 指定のクラスローダをインポートの一覧に含めます.
 * @param self
 * @param target
 * @return
 */
struct ImportInfo* ImportImportManager(import_manager* self, struct class_loader* target);

/**
 * 既に読み込まれたなら true.
 * @param self
 * @param index
 * @return
 */
bool IsLoadedImportManager(import_manager* self, int index);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param scope
 * @param fqcn
 * @param cctx
 * @return 解決出来なかったなら NULL を返します.
 */
struct generic_type* ResolveImportManager(struct namespace_* scope, struct generic_cache* fqcn, struct CallContext* cctx);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param scope
 * @param fqcn
 * @param cctx
 * @return 解決出来なかったなら NULL を返します.
 */
struct generic_type* ResolvefImportManager(struct namespace_* scope, struct fqcn_cache* fqcn, struct CallContext* cctx);

/**
 * インポートマネージャを開放します.
 * @param self
 */
void DeleteImportManager(import_manager* self);
#endif // !SIGNAL_ENV_IMPORT_MANAGER_H
