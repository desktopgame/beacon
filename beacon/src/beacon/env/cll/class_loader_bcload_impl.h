#ifndef BEACON_ENV_CLASS_LOADER_SGLOAD_IMPL_H
#define BEACON_ENV_CLASS_LOADER_SGLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "../class_loader.h"
#include "../link_type.h"

/**
 * 全ての中間言語をもっとも抽象的なモデルであるSGへ変換します.
 * SGは静的に型付けされたクラス階層をそのまま表現します。
 * @param self
 */
void BCLoadClassLoader(class_loader* self);

/**
 * beacon/langを仮読み込みするための関数.
 * @param self
 */
void SpecialBCLoadClassLoader(class_loader* self);
#endif
