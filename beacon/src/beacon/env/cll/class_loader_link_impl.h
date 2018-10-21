#ifndef BEACON_ENV_CLL_LINK_IMPL_H
#define BEACON_ENV_CLL_LINK_IMPL_H
#include "../class_loader.h"

/**
 * 指定のクラスローダーをリンクします.
 * @param self
 * @param type
 */
void LinkClassLoader(class_loader* self, LinkType type);
#endif