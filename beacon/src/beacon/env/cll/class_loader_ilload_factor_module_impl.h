#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_FACTOR_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_FACTOR_MODULE_IMPL_H

struct class_loader;
struct ast;
struct il_factor;
/**
 * 因子を IL に変換します.
 * @param self
 * @param source
 * @return
 */
struct il_factor* CLILFactor(struct class_loader* self, struct ast* source);
#endif