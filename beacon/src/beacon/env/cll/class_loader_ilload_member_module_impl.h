// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_loader_ilload_member_module_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_MEMBER_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_MEMBER_MODULE_IMPL_H
#include "../../il/il_type_interface.h"
#include "../class_loader.h"

/**
 * メンバーツリーを IL に変換します.
 * メンバーツリーとは、"アクセス修飾子とメンバーリストのペア"のリストです。
 * つまり、C++のメンバー定義を模倣した構文をモデル化します。
 * @param self
 * @param current
 * @param atree
 */
void CLILMemberTree(bc_ClassLoader* self, bc_ILType* current, bc_AST* atree);

/**
 * メンバーを IL に変換します.
 * メンバーはクラスに含めることが出来る要素(フィールド/メソッド/コンストラクタ)のことです。
 * @param self
 * @param current
 * @param amember
 * @param level
 */
void CLILMemberList(bc_ClassLoader* self, bc_ILType* current, bc_AST* amember,
                    bc_AccessLevel level);

/**
 * フィールドを IL に変換します.
 * @param self
 * @param current
 * @param afield
 * @param level
 */
void CLILField(bc_ClassLoader* self, bc_ILType* current, bc_AST* afield,
               bc_AccessLevel level);

/**
 * プロパティを IL に変換します.
 * @param self
 * @param current
 * @param aprop
 * @param level
 */
void CLILProperty(bc_ClassLoader* self, bc_ILType* current, bc_AST* aprop,
                  bc_AccessLevel level);

/**
 * メソッドを IL に変換します.
 * @param self
 * @param current
 * @param amethod
 * @param level
 */
void CLILMethod(bc_ClassLoader* self, bc_ILType* current, bc_AST* amethod,
                bc_AccessLevel level);

/**
 * コンストラクタを IL に変換します.
 * @param self
 * @param current
 * @param aconstructor
 * @param level
 */
void CLILConstructor(bc_ClassLoader* self, bc_ILType* current,
                     bc_AST* aconstructor, bc_AccessLevel level);

/**
 * 演算子オーバーロードを IL に変換します.
 * @param self
 * @param current
 * @param aopov
 * @param level
 */
void CLILOperatorOverload(bc_ClassLoader* self, bc_ILType* current,
                          bc_AST* aopov, bc_AccessLevel level);
#endif