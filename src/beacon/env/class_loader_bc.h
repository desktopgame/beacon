#ifndef BEACON_ENV_CLASS_LOADER_BC_H
#define BEACON_ENV_CLASS_LOADER_BC_H
#include "../util/vector.h"
struct bc_ClassLoader;
struct bc_Enviroment;
struct bc_Namespace;
struct bc_CallContext;

struct bc_ClassLoader* CLBC_import_new(struct bc_ClassLoader* self,
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