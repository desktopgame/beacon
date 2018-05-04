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
void class_loader_bcload_impl(class_loader* self);

void CLBC_namespace_tree(class_loader* self);
#endif
