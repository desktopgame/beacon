#ifndef SIGNAL_ENV_CLASS_LOADER_ILLOAD_IMPL_H
#define SIGNAL_ENV_CLASS_LOADER_ILLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "class_loader.h"
#include "../il/il_namespace.h"
#include "../il/il_factor_impl.h"
#include "../il/il_stmt_impl.h"

void class_loader_ilload_impl(class_loader* self, ast* source_code);
void class_loader_ilload_import(class_loader* self, ast* import_decl);
void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl);
void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);
il_namespace* class_loader_ilload_ast_to_namespace(ast* a);
void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body);
void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl);
void class_loader_ilload_member_tree(class_loader* self, il_type* current, ast* tree);
void class_loader_ilload_member(class_loader* self, il_type* current, ast* member, access_level level);
void class_loader_ilload_field(class_loader* self, il_type* current, ast* field, access_level level);
void class_loader_ilload_method(class_loader* self, il_type* current, ast* method, access_level level);
void class_loader_ilload_constructor(class_loader* self, il_type* current, ast* constructor, access_level level);
void class_loader_ilload_param(class_loader* self, vector* list, ast* source);
void class_loader_ilload_body(class_loader* self, vector* list, ast* source);
il_stmt_variable_decl* class_loader_ilload_variable_decl(class_loader* self, ast* source);
il_stmt_variable_init* class_loader_ilload_variable_init(class_loader* self, ast* source);
il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source);
il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source);
void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source);
il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source);
il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source);
il_stmt_return* class_loader_ilload_return(class_loader* self, ast* source);
il_factor* class_loader_ilload_factor(class_loader* self, ast* source);
il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type);
il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type);
il_factor_call* class_loader_ilload_call(class_loader* self, ast* source);
il_factor_invoke* class_loader_ilload_invoke(class_loader* self, ast* source);
il_factor_named_invoke* class_loader_ilload_named_invoke(class_loader* self, ast* source);
il_factor_new_instance* class_loader_ilload_new_instance(class_loader* self, ast* source);
il_factor_field_access* class_loader_ilload_field_access(class_loader* self, ast* source);
il_factor_static_field_access* class_loader_ilload_static_field_access(class_loader* self, ast* source);
void class_loader_ilload_fqcn(ast* fqcn, fqcn_cache* dest);
void class_loader_ilload_fqcn_impl(ast* fqcn, fqcn_cache* dest);
void class_loader_ilload_argument_list(class_loader* self, vector* list, ast* source);
#endif