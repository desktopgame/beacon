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
 * @param tree
 */
void CLIL_member_tree(class_loader* self, il_type* current, ast* tree);

/**
 * メンバーを IL に変換します.
 * メンバーはクラスに含めることが出来る要素(フィールド/メソッド/コンストラクタ)のことです。
 * @param self
 * @param current
 * @param member
 * @param level
 */
void CLIL_member_list(class_loader* self, il_type* current, ast* member, access_level level);

/**
 * フィールドを IL に変換します.
 * @param self
 * @param current
 * @param field
 * @param level
 */
void CLIL_field(class_loader* self, il_type* current, ast* field, access_level level);

/**
 * プロパティを IL に変換します.
 * @param self
 * @param current
 * @param aprop
 * @param level
 */
void CLIL_prop(class_loader* self, il_type* current, ast* aprop, access_level level);

/**
 * メソッドを IL に変換します.
 * @param self
 * @param current
 * @param method
 * @param level
 */
void CLIL_method(class_loader* self, il_type* current, ast* method, access_level level);

/**
 * コンストラクタを IL に変換します.
 * @param self
 * @param current
 * @param constructor
 * @param level
 */
void CLIL_ctor(class_loader* self, il_type* current, ast* constructor, access_level level);

/**
 * 演算子オーバーロードを IL に変換します.
 * @param self
 * @param current
 * @param opov
 * @param level
 */
void CLIL_operator_overload(class_loader* self, il_type* current, ast* opov, access_level level);
#endif