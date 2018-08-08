#ifndef BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#include "../class_loader.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_field.h"
#include "../../il/call_context.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/field.h"

bool CLBC_field_decl(class_loader* self, il_type* iltype, type* tp, il_field* ilfi, namespace_* scope, call_context* cctx);
bool CLBC_field_impl(class_loader* self, type* tp, field* fi, namespace_* scope, call_context* cctx);
/**
 * フィールド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilfields
 */
void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, vector* ilfields, namespace_* scope);
void CLBC_fields_impl(class_loader* self, namespace_* scope, type* tp,vector* ilfields, vector* sgfields);

/**
 * @param self
 * @param iltype
 * @param tp
 * @param scope
 */
void CLBC_property_decl(class_loader* self, il_type* iltype, type* tp, vector* ilprops, namespace_* scope);
void CLBC_property_impl(class_loader* self, il_type* iltype, type* tp, vector* ilprops, vector* sgprops, namespace_* scope);

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

void CLBC_body(class_loader* self, vector* stmt_list, struct enviroment* dest, call_context* cctx, namespace_* range);
#endif