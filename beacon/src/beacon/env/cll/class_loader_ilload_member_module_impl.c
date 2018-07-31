#include "class_loader_ilload_member_module_impl.h"
#include "../../il/il_type_impl.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_operator_overload.h"
#include "../../il/il_property.h"
#include "../../error.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>

static il_property_body* CLIL_prop_body(class_loader* self, il_type* current, ast* abody, il_property_body_tag tag, access_level level);

void CLIL_member_tree(class_loader* self, il_type* current, ast* tree) {
	if (tree->tag == ast_access_member_tree) {
		for (int i = 0; i < tree->vchildren->length; i++) {
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
		for(int i=0; i<member->vchildren->length; i++) {
			CLIL_member_list(self, current, ast_at(member, i), level);
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			CLIL_field(self, current, child, level);
		} else if(child->tag == ast_prop_decl) {
			CLIL_prop(self, current, child, level);
		} else if (child->tag == ast_method_decl) {
			CLIL_method(self, current, child, level);
		} else if (child->tag == ast_constructor_decl) {
			CLIL_ctor(self, current, child, level);
		} else if(child->tag == ast_operator_overload) {
			CLIL_operator_overload(self, current, child, level);
		}
	}
}

void CLIL_field(class_loader* self, il_type* current, ast* field, access_level level) {
	assert(current->tag == iltype_class);
	ast* modifier = ast_first(field);
	ast* type_name = ast_second(field);
	ast* access_name = ast_at(field, 2);
	il_field* v = il_field_new(access_name->u.stringv_value);
	CLIL_generic_cache(type_name, v->fqcn);
	bool error;
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier, &error);
	il_type_add_field(current, v);
	//重複する修飾子を検出
	if(error) {
		bc_error_throw(bcerror_modifier_a_overlapped, string_pool_ref2str(v->namev));
	}
}

void CLIL_prop(class_loader* self, il_type* current, ast* aprop, access_level level) {
	ast* amod = ast_at(aprop, 0);
	ast* atypename = ast_at(aprop, 1);
	ast* aset = ast_at(aprop, 2);
	ast* aget = ast_at(aprop, 3);
	string_view propname = aprop->u.stringv_value;
	il_property* ret = il_property_new(propname);
	CLIL_generic_cache(atypename, ret->fqcn);
	if(ast_is_blank(amod)) {
		ret->modifier = modifier_none;
	} else {
		ret->modifier = amod->u.modifier_value;
	}
	ret->access = level;
	ret->set = CLIL_prop_body(self, current, aset, ilproperty_set, level);
	ret->get = CLIL_prop_body(self, current, aget, ilproperty_get, level);
	il_type_add_property(current, ret);
	if(ret->set->is_short != ret->get->is_short) {
		bc_error_throw(bcerror_invalid_property_decl, string_pool_ref2str(current->u.class_->namev), string_pool_ref2str(propname));
	}
}

void CLIL_method(class_loader* self, il_type* current, ast* method, access_level level) {
	assert(current->tag == iltype_class || current->tag == iltype_interface);
	ast* modifier = ast_at(method, 0);
	ast* func_name = ast_at(method, 1);
	ast* ageneric = ast_at(method, 2);
	ast* param_list = ast_at(method, 3);
	ast* func_body = ast_at(method, 4);
	ast* ret_name = ast_at(method, 5);
	il_method* v = il_method_new(func_name->u.stringv_value);
	CLIL_type_parameter(self, ageneric, v->type_parameter_list);
	CLIL_generic_cache(ret_name, v->return_fqcn);
	bool error;
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier, &error);
	CLIL_parameter_list(self, v->parameter_list, param_list);
	CLIL_body(self, v->statement_list, func_body);
	//メソッドの本文が省略されているかどうか
	//例えばネイティブメソッドや抽象メソッドは省略されているべき
	if(ast_is_blank(func_body)) {
		v->no_stmt = true;
	}
	il_type_add_method(current, v);
	//重複する修飾子を検出
	if(error) {
		bc_error_throw(bcerror_modifier_a_overlapped, string_pool_ref2str(v->namev));
	}
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

void CLIL_operator_overload(class_loader* self, il_type* current, ast* opov, access_level level) {
	assert(opov->tag == ast_operator_overload);
	operator_type ot = opov->u.operator_value;
	ast* aparam_list = ast_at(opov, 0);
	ast* abody = ast_at(opov, 1);
	ast* areturn = ast_at(opov, 2);
	il_operator_overload* ilopov = il_operator_overload_new(ot);
	ilopov->access = level;
	CLIL_parameter_list(self, ilopov->parameter_list, aparam_list);
	CLIL_body(self, ilopov->statement_list, abody);
	CLIL_generic_cache(areturn, ilopov->return_fqcn);
	vector_push(current->u.class_->operator_overload_list, ilopov);
}
//private
static il_property_body* CLIL_prop_body(class_loader* self, il_type* current, ast* abody, il_property_body_tag tag, access_level level) {
	il_property_body* ret = il_property_body_new(tag);
	assert(abody->tag == ast_prop_set || abody->tag == ast_prop_get);
	ast* aacess = ast_first(abody);
	ast* astmt_list = ast_second(abody);
	ret->access = level;
	CLIL_body(self, ret->statement_list, astmt_list);
	if(!ast_is_blank(aacess)) {
		ret->access = aacess->u.access_value;
	}
	if(ret->statement_list->length == 0) {
		ret->is_short = true;
	}
	return ret;
}