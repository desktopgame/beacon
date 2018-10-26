#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_MEMBER_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_MEMBER_MODULE_IMPL_H
#include "../class_loader.h"
#include "../../il/il_type_interface.h"

/**
 * メンバーツリーを IL に変換します.
 * メンバーツリーとは、"アクセス修飾子とメンバーリストのペア"のリストです。
 * つまり、C++のメンバー定義を模倣した構文をモデル化します。
 * @param self
 * @param current
 * @param atree
 */
void CLILMemberTree(ClassLoader* self, il_type* current, AST* atree);

/**
 * メンバーを IL に変換します.
 * メンバーはクラスに含めることが出来る要素(フィールド/メソッド/コンストラクタ)のことです。
 * @param self
 * @param current
 * @param amember
 * @param level
 */
void CLILMemberList(ClassLoader* self, il_type* current, AST* amember, AccessLevel level);

/**
 * フィールドを IL に変換します.
 * @param self
 * @param current
 * @param afield
 * @param level
 */
void CLILField(ClassLoader* self, il_type* current, AST* afield, AccessLevel level);

/**
 * プロパティを IL に変換します.
 * @param self
 * @param current
 * @param aprop
 * @param level
 */
void CLILProperty(ClassLoader* self, il_type* current, AST* aprop, AccessLevel level);

/**
 * メソッドを IL に変換します.
 * @param self
 * @param current
 * @param amethod
 * @param level
 */
void CLILMethod(ClassLoader* self, il_type* current, AST* amethod, AccessLevel level);

/**
 * コンストラクタを IL に変換します.
 * @param self
 * @param current
 * @param aconstructor
 * @param level
 */
void CLILConstructor(ClassLoader* self, il_type* current, AST* aconstructor, AccessLevel level);

/**
 * 演算子オーバーロードを IL に変換します.
 * @param self
 * @param current
 * @param aopov
 * @param level
 */
void CLILOperatorOverload(ClassLoader* self, il_type* current, AST* aopov, AccessLevel level);
#endif