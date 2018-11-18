//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_loader_ilload_factor_module_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_FACTOR_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_FACTOR_MODULE_IMPL_H

struct bc_ClassLoader;
struct bc_AST;
struct ILFactor;
/**
 * 因子を IL に変換します.
 * @param self
 * @param source
 * @return
 */
struct ILFactor* CLILFactor(struct bc_ClassLoader* self, struct bc_AST* source);
#endif