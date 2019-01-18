#ifndef BEACON_ENV_CLASS_LOADER_BC_H
#define BEACON_ENV_CLASS_LOADER_BC_H
struct bc_ClassLoader;

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