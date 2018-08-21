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
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>

static il_property_body* CLIL_prop_body(class_loader* self, il_type* current, ast* abody, il_property_body_tag tag, access_level level);

void CLIL_member_tree(class_loader* self, il_type* current, ast* atree) {
	if (atree->tag == ast_access_member_tree_T) {
		for (int i = 0; i < atree->vchildren->length; i++) {
			CLIL_member_tree(self, current, ast_at(atree, i));
		}
	} else if (atree->tag == ast_access_member_list_T) {
		ast* aaccess = ast_first(atree);
		ast* amember_list = ast_second(atree);
		access_level level = ast_cast_T_to_access(aaccess);
		CLIL_member_list(self, current, amember_list, level);
	}
}

void CLIL_member_list(class_loader* self, il_type* current, ast* amember, access_level level) {
	if(amember->tag == ast_member_decl_T_list) {
		for(int i=0; i<amember->vchildren->length; i++) {
			CLIL_member_list(self, current, ast_at(amember, i), level);
		}
	} else if(amember->tag == ast_member_decl_T) {
		ast* achild = ast_first(amember);
		if (achild->tag == ast_field_decl_T) {
			CLIL_field(self, current, achild, level);
		} else if(achild->tag == ast_prop_decl_T) {
			CLIL_prop(self, current, achild, level);
		} else if (achild->tag == ast_method_decl_T) {
			CLIL_method(self, current, achild, level);
		} else if (achild->tag == ast_constructor_decl_T) {
			CLIL_ctor(self, current, achild, level);
		} else if(achild->tag == ast_operator_overload_T) {
			CLIL_operator_overload(self, current, achild, level);
		}
	}
}

void CLIL_field(class_loader* self, il_type* current, ast* afield, access_level level) {
	assert(current->tag == iltype_class);
	ast* amodifier = ast_first(afield);
	ast* atype_name = ast_second(afield);
	ast* aaccess_name = ast_at(afield, 2);
	ast* afact = ast_at(afield, 3);
	il_field* v = il_field_new(aaccess_name->u.stringv_value);
	CLIL_generic_cache(atype_name, v->fqcn);
	bool error;
	v->access = level;
	v->modifier = ast_cast_T_to_modifier(amodifier, &error);
	il_type_add_field(current, v);
	//設定されているなら初期値も
	if(!ast_is_blank(afact)) {
		v->initial_value = CLIL_factor(self, afact);
	}
	//重複する修飾子を検出
	if(error) {
		bc_error_throw(bcerror_overwrap_modifier, string_pool_ref2str(v->namev));
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
		bool err = false;
		ret->modifier = ast_cast_T_to_modifier(amod, &err);
		if(err) {
			bc_error_throw(bcerror_overwrap_modifier, string_pool_ref2str(ret->namev));
		}
	}
	ret->access = level;
	ret->set = CLIL_prop_body(self, current, aset, ilproperty_set, level);
	ret->get = CLIL_prop_body(self, current, aget, ilproperty_get, level);
	il_type_add_property(current, ret);
	if(ret->set->is_short != ret->get->is_short) {
		bc_error_throw(bcerror_invalid_property_decl, string_pool_ref2str(current->u.class_->namev), string_pool_ref2str(propname));
	}
}

void CLIL_method(class_loader* self, il_type* current, ast* amethod, access_level level) {
	assert(current->tag == iltype_class || current->tag == iltype_interface);
	ast* amodifier = ast_at(amethod, 0);
	ast* afunc_name = ast_at(amethod, 1);
	ast* ageneric = ast_at(amethod, 2);
	ast* aparam_list = ast_at(amethod, 3);
	ast* afunc_body = ast_at(amethod, 4);
	ast* aret_name = ast_at(amethod, 5);
	il_method* v = il_method_new(afunc_name->u.stringv_value);
	CLIL_type_parameter(self, ageneric, v->type_parameter_list);
	CLIL_generic_cache(aret_name, v->return_fqcn);
	bool error;
	v->access = level;
	v->modifier = ast_cast_T_to_modifier(amodifier, &error);
	CLIL_parameter_list(self, v->parameter_list, aparam_list);
	CLIL_body(self, v->statement_list, afunc_body);
	//メソッドの本文が省略されているかどうか
	//例えばネイティブメソッドや抽象メソッドは省略されているべき
	if(ast_is_blank(afunc_body)) {
		v->no_stmt = true;
	}
	il_type_add_method(current, v);
	//重複する修飾子を検出
	if(error) {
		bc_error_throw(bcerror_overwrap_modifier, string_pool_ref2str(v->namev));
	}
}

void CLIL_ctor(class_loader* self, il_type* current, ast* aconstructor, access_level level) {
	assert(current->tag == iltype_class);
	ast* aparams = ast_at(aconstructor, 0);
	ast* achain = ast_at(aconstructor, 1);
	ast* abody = ast_at(aconstructor, 2);
	il_constructor_chain* ilchain = NULL;
	if (!ast_is_blank(achain)) {
		ast* achain_type = ast_first(achain);
		ast* aargs = ast_second(achain);
		ilchain = il_constructor_chain_new();
		ilchain->type = ast_cast_T_to_chain_type(achain_type);
		CLIL_argument_list(self, ilchain->argument_list, aargs);
	}
	il_constructor* ilcons = il_constructor_new();
	ilcons->access = level;
	ilcons->chain = ilchain;
	CLIL_parameter_list(self, ilcons->parameter_list, aparams);
	CLIL_body(self, ilcons->statement_list, abody);
	vector_push(current->u.class_->constructor_list, ilcons);
}

void CLIL_operator_overload(class_loader* self, il_type* current, ast* aopov, access_level level) {
	assert(aopov->tag == ast_operator_overload_T);
	operator_type ot = aopov->u.operator_value;
	ast* aparam_list = ast_at(aopov, 0);
	ast* abody = ast_at(aopov, 1);
	ast* areturn = ast_at(aopov, 2);
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
	assert(abody->tag == ast_prop_set_T || abody->tag == ast_prop_get_T);
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