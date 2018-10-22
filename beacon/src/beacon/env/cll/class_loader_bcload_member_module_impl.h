#ifndef BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_MEMBER_MODULE_IMPL_H
#include "../class_loader.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_field.h"
#include "../../il/il_property.h"
#include "../../il/il_method.h"
#include "../../il/il_operator_overload.h"
#include "../../il/call_context.h"
#include "../../il/il_constructor.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/method.h"
#include "../../env/field.h"
#include "../../env/constructor.h"
#include "../../env/operator_overload.h"
#include "../../env/property.h"

bool CLBC_field_decl(class_loader* self, il_type* iltype, type* tp, il_field* ilfi, namespace_* scope, CallContext* cctx);
bool CLBC_field_impl(class_loader* self, type* tp, field* fi, namespace_* scope, CallContext* cctx);
/**
 * フィールド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilfields
 */
void CLBC_fields_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilfields, namespace_* scope);
void CLBC_fields_impl(class_loader* self, namespace_* scope, type* tp,Vector* ilfields, Vector* sgfields);

bool CLBC_property_decl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, namespace_* scope, CallContext* cctx);
bool CLBC_property_impl(class_loader* self, il_type* iltype, type* tp, il_property* ilprop, property* prop, namespace_* scope, CallContext* cctx);

/**
 * @param self
 * @param iltype
 * @param tp
 * @param scope
 */
void CLBC_properties_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilprops, namespace_* scope);
void CLBC_properties_impl(class_loader* self, il_type* iltype, type* tp, Vector* ilprops, Vector* sgprops, namespace_* scope);

bool CLBC_method_decl(class_loader* self, il_type* iltype, type* tp, il_method* ilmt, namespace_* scope);
bool CLBC_method_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, il_method* ilmt, method* mt);

/**
 * メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilmethods
 * @param scope
 */
void CLBC_methods_decl(class_loader* self, il_type* iltype, type* tp, Vector* ilmethods, namespace_* scope);
void CLBC_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, Vector* ilmethods, Vector* sgmethods);


bool CLBC_ctor_decl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, namespace_* scope);
bool CLBC_ctor_impl(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, constructor* cons, namespace_* scope);

/**
 * コンストラクタ宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param scope
 */
void CLBC_ctors_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
void CLBC_ctors_impl(class_loader* self, il_type* iltype, type* tp);

bool CLBC_operator_overload_decl(class_loader* self, il_type* iltype, type* tp, il_operator_overload* ilopov, namespace_* scope);
bool CLBC_operator_overload_impl(class_loader* self, il_type* iltype, type* tp, il_operator_overload* ilopov, operator_overload* opov, namespace_* scope);

void CLBC_operator_overloads_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
void CLBC_operator_overloads_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

bool CLBC_corutine(class_loader* self, method* mt, Enviroment* env, Vector* ilparams, Vector* ilstmts, CallContext* cctx, namespace_* range);

void CLBC_body(class_loader* self, Vector* stmt_list, Enviroment* dest, CallContext* cctx, namespace_* range);
#endif