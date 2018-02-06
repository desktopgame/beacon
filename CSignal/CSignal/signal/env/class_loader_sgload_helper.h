#pragma once
#ifndef SIGNAL_ENV_CLASS_LOADER_SGLOAD_HELPER_H
#define SIGNAL_ENV_CLASS_LOADER_SGLOAD_HELPER_H
//このヘッダーは class_loader_sgload_impl.h 以外からはインクルードしないでください。
#include "class_loader.h"
#include "../il/il_namespace.h"
#include "../il/il_type_interface.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_method.h"
#include "type_interface.h"
#include "type_impl.h"

void class_loader_sgload_class_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
void class_loader_sgload_class_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

void class_loader_sgload_interface_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
void class_loader_sgload_interface_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

/**
 * インスタンス/静的メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 */
void class_loader_sgload_methods(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

/**
 * メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilmethods
 * @param scope
 */
void class_loader_sgload_methods_impl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods, namespace_* scope);


void class_loader_sgload_complete_methods(class_loader* self, il_type* iltype, type* tp);
void class_loader_sgload_complete_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods);
#endif // !SIGNAL_ENV_CLASS_LOADER_SGLOAD_HELPER_H
