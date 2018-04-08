#ifndef BEACON_ENV_CLASS_LOADER_ILLOAD_IMPL_H
#define BEACON_ENV_CLASS_LOADER_ILLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "../class_loader.h"
#include "../../il/il_namespace.h"
#include "../../il/il_factor_impl.h"
#include "../../il/il_stmt_impl.h"
#include "../generic_cache.h"

/**
 * ASTの全てのエントリを IL に変換します.
 * @param self
 * @param source_code
 */
void class_loader_ilload_impl(class_loader* self, ast* source_code);

/**
 * トップレベルの関数宣言を IL に変換します.
 * @param self
 * @param source
 */
void class_loader_ilload_function(class_loader* self, ast* source);

/**
 * インポートの一覧を IL に変換します.
 * @param self
 * @param source
 */
void class_loader_ilload_import_list(class_loader* self, ast* source);

/**
 * インポート宣言を IL に変換します.
 * @param self
 * @param import_decl
 */
void class_loader_ilload_import(class_loader* self, ast* import_decl);

/**
 * 名前空間とその内側のエントリ全てを IL に変換します.
 * @param self
 * @param parent
 * @param namespace_decl
 */
void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl);

/**
 * 名前空間のパス(A.B.C)を解析します.
 * デバッグ用の関数で、今は特に何も行いません。
 * @param self
 * @param namespace_path
 * @param namespace_body
 */
void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);

/**
 * 名前空間(またはそのリスト)を IL に変換します.
 * @param a
 * @return
 */
il_namespace* class_loader_ilload_ast_to_namespace(ast* a);

/**
 * 名前空間の内側に定義される要素を IL に変換します.
 * @param self
 * @param current
 * @param parent
 * @param namespace_body
 */
void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body);

/**
 * クラス宣言を IL に変換します.
 * @param self
 * @param current
 * @param class_decl
 */
void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl);
void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* interface_decl);
void class_loader_ilload_enum(class_loader* self, il_namespace* current, ast* enum_decl);

/**
 * 型名の一覧を dst へ出力します.
 * @param self
 * @param dst
 * @param typename_list
 */
void class_loader_ilload_typename_list(class_loader* self, vector* dst, ast* typename_list);

/**
 * 識別子を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
void class_loader_ilload_identifier_list(class_loader* self, vector* list, ast* source);

#endif
