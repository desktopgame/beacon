#ifndef SIGNAL_ENV_CLASS_LOADER_SGLOAD_IMPL_H
#define SIGNAL_ENV_CLASS_LOADER_SGLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "class_loader.h"
#include "../il/il_namespace.h"
#include "../il/il_type_interface.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_method.h"
#include "type_interface.h"
#include "type_impl.h"

/**
 * 全ての中間言語をもっとも抽象的なモデルであるSGへ変換します.
 * SGは静的に型付けされたクラス階層をそのまま表現します。
 * @param self
 */
void class_loader_sgload_impl(class_loader* self);

/**
 * インポートの一覧を確認して、読み込むべきファイルがあるなら読み込みます.
 * @param self
 * @param ilimports
 */
void class_loader_sgload_import(class_loader* self, vector* ilimports);

/**
 * 名前空間の一覧を読み込みます.
 * @param self
 * @param ilnamespace_list
 * @param parent
 */
void class_loader_sgload_namespace_list(class_loader* self, vector* ilnamespace_list, namespace_* parent);

/**
 * 名前空間と含まれるエントリの一覧を読み込みます.
 * @param self
 * @param ilnamespace
 * @param parent
 */
void class_loader_sgload_namespace(class_loader* self, il_namespace* ilnamespace, namespace_* parent);

/**
 * 型宣言の一覧を読み込みます.
 * @param self
 * @param iltype_list
 * @param parent
 */
void class_loader_sgload_type_list(class_loader* self, vector* iltype_list, namespace_* parent);

/**
 * クラス宣言を読み込んで名前空間に登録します.
 * @param self
 * @param iltype
 * @param parent
 */
void class_loader_sgload_class(class_loader* self, il_type* iltype, namespace_* parent);

/**
 * インスタンス/静的フィールド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 */
void class_loader_sgload_fields(class_loader* self, il_type* iltype, type* tp);

/**
 * フィールド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilfields
 */
void class_loader_sgload_fields_impl(class_loader* self, il_type* iltype, type* tp, vector* ilfields);

/**
 * インスタンス/静的メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 */
void class_loader_sgload_methods(class_loader* self, il_type* iltype, type* tp);


/**
 * メソッド宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 * @param ilmethods
 */
void class_loader_sgload_methods_impl(class_loader* self, il_type* iltype, type* tp, vector* ilmethods);

/**
 * コンストラクタ宣言を読み込んでクラスに追加します.
 * @param self
 * @param iltype
 * @param tp
 */
void class_loader_sgload_constructors(class_loader* self, il_type* iltype, type* tp);

/**
 * クラスとメンバーの一覧が登録されるまで保留されていた作業を実行します.
 * @param self
 * @param iltype
 * @param tp
 */
void class_loader_sgload_complete(class_loader* self, il_type* iltype, type* tp);
void class_loader_sgload_complete_fields(class_loader* self, il_type* iltype, type* tp);
void class_loader_sgload_complete_fields_impl(class_loader* self, namespace_* scope, vector* ilfields, vector* sgfields);
void class_loader_sgload_complete_methods(class_loader* self, il_type* iltype, type* tp);
void class_loader_sgload_complete_methods_impl(class_loader* self, namespace_* scope, il_type* iltype, type* tp, vector* ilmethods, vector* sgmethods);
void class_loader_sgload_complete_constructors(class_loader* self, il_type* iltype, type* tp);
void class_loader_sgload_params(class_loader* self, namespace_* scope, vector* param_list, vector* sg_param_liste);
void class_loader_sgload_chain(class_loader* self, il_type* iltype, type* tp, il_constructor* ilcons, il_constructor_chain* ilchain, enviroment* env);
void class_loader_sgload_attach_native_method(class_loader* self, il_type* iltype, class_* classz, il_method* ilmethod, method* me);
void class_loader_sgload_debug_native_method(method* parent, vm* vm, enviroment* env);
void class_loader_sgload_body(class_loader* self, vector* stmt_list, enviroment* dest, namespace_* range);
#endif