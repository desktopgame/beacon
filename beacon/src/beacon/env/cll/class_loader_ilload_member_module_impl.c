#include "class_loader_ilload_member_module_impl.h"
#include "../../il/il_type_impl.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>


void CLIL_member_tree(class_loader* self, il_type* current, ast* tree) {
	if (tree->tag == ast_access_member_tree) {
		for (int i = 0; i < tree->child_count; i++) {
			CLIL_member_tree(self, current, ast_at(tree, i));
		}
	} else if (tree->tag == ast_access_member_list) {
		ast* access = ast_first(tree);
		ast* member_list = ast_second(tree);
		access_level level = ast_cast_to_access(access);
		CLIL_member_list(self, current, member_list, level);
	}
}

void CLIL_member_list(class_loader* self, il_type* current, ast* member, access_level level) {
	if(member->tag == ast_member_decl_list) {
		for(int i=0; i<member->child_count; i++) {
			CLIL_member_list(self, current, ast_at(member, i), level);
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			CLIL_field(self, current, child, level);
		} else if (child->tag == ast_method_decl) {
			CLIL_method(self, current, child, level);
		} else if (child->tag == ast_constructor_decl) {
			CLIL_ctor(self, current, child, level);
		}
	}
}

void CLIL_field(class_loader* self, il_type* current, ast* field, access_level level) {
	assert(current->tag == iltype_class);
	ast* modifier = ast_first(field);
	ast* type_name = ast_second(field);
	ast* access_name = ast_at(field, 2);
	il_field* v = il_field_new(access_name->u.string_value);
	CLIL_generic_cache(type_name, v->fqcn);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	il_type_add_field(current, v);
}

void CLIL_method(class_loader* self, il_type* current, ast* method, access_level level) {
	assert(current->tag == iltype_class || current->tag == iltype_interface);
	ast* modifier = ast_at(method, 0);
	ast* func_name = ast_at(method, 1);
	ast* ageneric = ast_at(method, 2);
	ast* param_list = ast_at(method, 3);
	ast* func_body = ast_at(method, 4);
	ast* ret_name = ast_at(method, 5);
	il_method* v = il_method_new(func_name->u.string_value);
	CLIL_type_parameter(self, ageneric, v->type_parameter_list);
	CLIL_generic_cache(ret_name, v->return_fqcn);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	CLIL_parameter_list(self, v->parameter_list, param_list);
	CLIL_body(self, v->statement_list, func_body);
	il_type_add_method(current, v);
}

void CLIL_ctor(class_loader* self, il_type* current, ast* constructor, access_level level) {
	assert(current->tag == iltype_class);
	ast* aparams = ast_at(constructor, 0);
	ast* achain = ast_at(constructor, 1);
	ast* abody = ast_at(constructor, 2);
	il_constructor_chain* ilchain = NULL;
	if (!ast_is_blank(achain)) {
		ast* achain_type = ast_first(achain);
		ast* aargs = ast_second(achain);
		ilchain = il_constructor_chain_new();
		ilchain->type = ast_cast_to_chain_type(achain_type);
		CLIL_argument_list(self, ilchain->argument_list, aargs);
	}
	il_constructor* ilcons = il_constructor_new();
	ilcons->access = level;
	ilcons->chain = ilchain;
	CLIL_parameter_list(self, ilcons->parameter_list, aparams);
	CLIL_body(self, ilcons->statement_list, abody);
	vector_push(current->u.class_->constructor_list, ilcons);
}