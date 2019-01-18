#ifndef BEACON_ENV_CLASS_LOADER_BC_H
#define BEACON_ENV_CLASS_LOADER_BC_H
#include "../util/vector.h"
struct bc_ClassLoader;
struct bc_Enviroment;
struct bc_Namespace;
struct bc_CallContext;

/**
 * selfがfullPathをインポートするためのクラスローダーを作成し、
 * selfと返されるクラスローダーの間に依存関係を構築します。
 * @param self
 * @param fullPath
 * @return
 */
struct bc_ClassLoader* bc_NewClassLoaderForImport(struct bc_ClassLoader* self,
                                                  char* fullPath);

/**
 * 中間表現を読み込んでクラスを生成します。
 * @param self
 */
void bc_LoadIL(struct bc_ClassLoader* self);

/**
 * 中間表現を読み込んでクラスを生成します。
 * @param self
 */
void bc_SpecialLoadIL(struct bc_ClassLoader* self);
#endif