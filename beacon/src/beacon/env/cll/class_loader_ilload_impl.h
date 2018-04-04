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
 * メンバーツリーを IL に変換します.
 * メンバーツリーとは、"アクセス修飾子とメンバーリストのペア"のリストです。
 * つまり、C++のメンバー定義を模倣した構文をモデル化します。
 * @param self
 * @param current
 * @param tree
 */
void class_loader_ilload_member_tree(class_loader* self, il_type* current, ast* tree);

/**
 * メンバーを IL に変換します.
 * メンバーはクラスに含めることが出来る要素(フィールド/メソッド/コンストラクタ)のことです。
 * @param self
 * @param current
 * @param member
 * @param level
 */
void class_loader_ilload_member(class_loader* self, il_type* current, ast* member, access_level level);

/**
 * フィールドを IL に変換します.
 * @param self
 * @param current
 * @param field
 * @param level
 */
void class_loader_ilload_field(class_loader* self, il_type* current, ast* field, access_level level);

/**
 * メソッドを IL に変換します.
 * @param self
 * @param current
 * @param method
 * @param level
 */
void class_loader_ilload_method(class_loader* self, il_type* current, ast* method, access_level level);

/**
 * コンストラクタを IL に変換します.
 * @param self
 * @param current
 * @param constructor
 * @param level
 */
void class_loader_ilload_constructor(class_loader* self, il_type* current, ast* constructor, access_level level);

/**
 * 識別子を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
void class_loader_ilload_identifier_list(class_loader* self, vector* list, ast* source);

/**
 * 仮引数を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
void class_loader_ilload_parameter_list(class_loader* self, vector* list, ast* source);

/**
 * ステートメントの一覧を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
void class_loader_ilload_body(class_loader* self, vector* list, ast* source);

/**
 * var宣言を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_inferenced_type_init* class_loader_ilload_inferenced_type_init(class_loader* self, ast* source);

/**
 * 変数宣言を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_variable_decl* class_loader_ilload_variable_decl(class_loader* self, ast* source);

/**
 * 変数初期化を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_variable_init* class_loader_ilload_variable_init(class_loader* self, ast* source);

/**
 * if(...) { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source);

/**
 * if(...) { ... } elif (...) { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source);

/**
 * elifの一覧を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source);

/**
 * if(...) { ... } else { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source);

/**
 * if(...) { ... } elif(...) { ... } else { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source);

/**
 * while ( ... ) { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_while* class_loader_ilload_while(class_loader* self, ast* source);

/**
 * return fact; を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_return* class_loader_ilload_return(class_loader* self, ast* source);

/**
 * try { ... } catch (A a) { ... } を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_stmt_try* class_loader_ilload_try(class_loader* self, ast* source);

/**
 * catch節の一覧を IL に変換して vector へ追加します.
 * @param self
 * @param dest
 * @param source
 */
void class_loader_ilload_catch_list(class_loader* self, vector* dest, ast* source);

/**
 * スローを IL に変換して返します.
 * @param self
 * @param source
 * @return
 */
il_stmt_throw* class_loader_ilload_throw(class_loader* self, ast* source);

/**
 * 因子を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_factor* class_loader_ilload_factor(class_loader* self, ast* source);

/**
 * trueを表すILを作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_bool* class_loader_ilload_true(class_loader* self, ast* source);

/**
 * falseを表すILを作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_bool* class_loader_ilload_false(class_loader* self, ast* source);

/**
 * キャストを IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_factor_cast* class_loader_ilload_cast(class_loader* self, ast* source);

/**
 * 単項演算子を IL に変換します.
 * @param self
 * @param source
 * @param type
 * @return
 */
il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type);

/**
 * 二項演算子を IL に変換します.
 * @param self
 * @param source
 * @param type
 * @return
 */
il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type);

il_factor_variable* class_loader_ilload_variable(class_loader* self, ast* source);
/**
 * インスタンス生成を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_factor_new_instance* class_loader_ilload_new_instance(class_loader* self, ast* source);


/**
 * asによる型変換を IL に変換します.
 * @param self
 * @param source
 * @return
 */
il_factor_as* class_loader_ilload_as(class_loader* self, ast* source);

/**
 * インクリメントを表す要素を作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_inc* class_loader_ilload_inc(class_loader* self, ast* source);
/**
 * デクリメントを表す要素を作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_dec* class_loader_ilload_dec(class_loader* self, ast* source);

/**
 * 関数呼び出し演算子を表す要素を作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_call_op* class_loader_ilload_call_op(class_loader* self, ast* source);

/**
 * メンバアクセスを表す要素を作成します.
 * @param self
 * @param source
 * @return
 */
il_factor_member_op* class_loader_ilload_member_op(class_loader* self, ast* source);

/**
 * 実引数の一覧を IL に変換して list へ格納します.
 * @param self
 * @param list
 * @param source
 */

#endif
