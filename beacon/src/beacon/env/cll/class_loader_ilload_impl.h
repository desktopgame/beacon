#ifndef BEACON_ENV_CLASS_LOADER_ILLOAD_IMPL_H
#define BEACON_ENV_CLASS_LOADER_ILLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "../class_loader.h"
#include "../../il/il_namespace.h"
#include "../../il/il_factor_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../generic_cache.h"

/**
 * ASTの全てのエントリを IL に変換します.
 * @param self
 * @param source_code
 */
void ILLoadClassLoader(class_loader* self, ast* source_code);

#endif
