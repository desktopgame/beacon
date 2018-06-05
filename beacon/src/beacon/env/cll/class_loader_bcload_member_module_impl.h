#ifndef BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#include "../class_loader.h"
#include "../../il/il_type_interface.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
/**
 * フィールド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilfields
 */
void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, vector* ilfields, namespace_* scope);
void CLBC_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields);

/**
 * メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilmethods
 * @param scope
 */
void CLBC_methods_decl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods, namespace_* scope);

void CLBC_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods);

/**
 * コンストラクタ宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param scope
 */
void CLBC_ctor_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

void CLBC_ctor_impl(class_loader* self, il_type* iltype, type* tp);

void CLBC_operator_overload_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

void CLBC_operator_overload_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

void CLBC_body(class_loader* self, vector* stmt_list, struct enviroment* dest, namespace_* range);
#endif