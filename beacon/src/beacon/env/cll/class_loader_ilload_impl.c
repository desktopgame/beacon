#include "class_loader_ilload_impl.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_type_impl.h"
#include "../../il/il_field.h"
#include "../../il/il_import.h"
#include "../../il/il_function.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_stmt_impl.h"
#include "../../il/il_type_argument.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
//
//ilload
//
#include "../../il/il_type_parameter.h"
//#include "../../il/il_type_parameter_rule.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_member_module_impl.h"

//proto

/**
 * トップレベルの関数宣言を IL に変換します.
 * @param self
 * @param source
 */
static void class_loader_ilload_function(class_loader* self, ast* asource);

/**
 * インポートの一覧を IL に変換します.
 * @param self
 * @param source
 */
static void class_loader_ilload_import_list(class_loader* self, ast* asource);

/**
 * インポート宣言を IL に変換します.
 * @param self
 * @param import_decl
 */
static void class_loader_ilload_import(class_loader* self, ast* aimport_decl);

/**
 * 名前空間とその内側のエントリ全てを IL に変換します.
 * @param self
 * @param parent
 * @param namespace_decl
 */
static void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* anamespace_decl);

/**
 * 名前空間のパス(A.B.C)を解析します.
 * デバッグ用の関数で、今は特に何も行いません。
 * @param self
 * @param namespace_path
 * @param namespace_body
 */
static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* anamespace_path, ast* namespace_body);

/**
 * 名前空間(またはそのリスト)を IL に変換します.
 * @param a
 * @return
 */
static il_namespace* class_loader_ilload_ast_to_namespace(ast* a);

/**
 * 名前空間の内側に定義される要素を IL に変換します.
 * @param self
 * @param current
 * @param parent
 * @param namespace_body
 */
static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* anamespace_body);

/**
 * クラス宣言を IL に変換します.
 * @param self
 * @param current
 * @param class_decl
 */
static void class_loader_ilload_abstract_class(class_loader* self, il_namespace* current, ast* aclass_decl);
static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* aclass_decl);
static il_class* class_loader_ilload_classImpl(class_loader* self, il_namespace* current, ast* aclass_decl);
static void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* ainterface_decl);
static void class_loader_ilload_enum(class_loader* self, il_namespace* current, ast* aenum_decl);

/**
 * 識別子を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
static void class_loader_ilload_identifier_list(class_loader* self, vector* list, ast* asource);

//static il_factor* CLIL_factorImpl(class_loader* self, ast* source);
//static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, ast* source);

void class_loader_ilload_impl(class_loader* self, ast* source_code) {
	assert(self->il_code == NULL);
	self->il_code = il_top_level_new();
	for (int i = 0; i < source_code->vchildren->length; i++) {
		ast* child = ast_at(self->source_code, i);
		//import a
		if (child->tag == ast_import_decl || child->tag == ast_import_decl_list) {
			class_loader_ilload_import_list(self, child);
		//namespace Foo { ... }
		} else if (child->tag == ast_namespace_decl) {
			class_loader_ilload_namespace(self, self->il_code->namespace_list, child);
		//print();
		} else if (ast_is_stmt(child)) {
			CLIL_body(self, self->il_code->statement_list, child);
		//def f() { ... }
		} else if(child->tag == ast_function_decl) {
			class_loader_ilload_function(self, child);
		} else {
			ast_print(child);
			io_println();
		}
	}
}

//private
static void class_loader_ilload_function(class_loader * self, ast * asource) {
	assert(asource->tag == ast_function_decl);
	ast* afunc_name = ast_at(asource, 0);
	ast* aparam_list = ast_at(asource, 1);
	ast* afunc_body = ast_at(asource, 2);
	ast* aret_name = ast_at(asource, 3);
	il_function* ilfunc = il_function_new(afunc_name->u.stringv_value);
	CLIL_parameter_list(self, ilfunc->parameter_list, aparam_list);
	CLIL_body(self, ilfunc->statement_list, afunc_body);
	CLIL_generic_cache(ast_first(aret_name), ilfunc->return_fqcn);
	vector_push(self->il_code->function_list, ilfunc);
}

static void class_loader_ilload_import_list(class_loader* self, ast* asource) {
	if(asource->tag == ast_import_decl_list) {
		for(int i=0; i<asource->vchildren->length; i++) {
			class_loader_ilload_import_list(self, ast_at(asource, i));
		}
	} else {
		assert(asource->tag == ast_import_decl);
		class_loader_ilload_import(self, asource);
	}
}

static void class_loader_ilload_import(class_loader* self, ast* aimport_decl) {
	assert(aimport_decl->tag == ast_import_decl);
	ast* apath = ast_first(aimport_decl);
	il_import* ret = il_import_new(apath->u.stringv_value);
	vector_push(self->il_code->import_list, ret);
}

static void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* anamespace_decl) {
	assert(anamespace_decl->tag == ast_namespace_decl);
	ast* anamespace_path = ast_first(anamespace_decl);
	ast* anamespace_body = ast_second(anamespace_decl);
	il_namespace* iln = class_loader_ilload_ast_to_namespace(anamespace_path);
	il_namespace* top = il_namespace_root(iln);
	vector_push(parent, top);
	class_loader_ilload_namespace_path_recursive(self, anamespace_path, anamespace_body);
	class_loader_ilload_namespace_body(self, iln, iln->namespace_list, anamespace_body);
}

static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* anamespace_path, ast* anamespace_body) {
	assert(anamespace_path->tag == ast_namespace_path ||
		   anamespace_path->tag == ast_namespace_path_list);
	if (anamespace_path->tag == ast_namespace_path) {
	} else if (anamespace_path->tag == ast_namespace_path_list) {
		for (int i = 0; i < anamespace_path->vchildren->length; i++) {
			class_loader_ilload_namespace_path_recursive(self, ast_at(anamespace_path, i), anamespace_body);
		}
	}
}

static il_namespace* class_loader_ilload_ast_to_namespace(ast* a) {
	assert(a->tag == ast_namespace_path ||
	       a->tag == ast_namespace_path_list);
	if(a->tag == ast_namespace_path) {
		il_namespace* ret = il_namespace_new(a->u.stringv_value);
		return ret;
	} else if(a->tag == ast_namespace_path_list) {
		ast* al = ast_first(a);
		ast* ar = ast_second(a);
		il_namespace* parent = class_loader_ilload_ast_to_namespace(al);
		il_namespace* child = class_loader_ilload_ast_to_namespace(ar);
		child->parent = parent;
		vector_push(parent->namespace_list, child);
		return child;
	}
	return NULL;
}

static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* anamespace_body) {
	if (ast_is_blank(anamespace_body)) {
		return;
	}
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (anamespace_body->tag == ast_namespace_decl) {
		class_loader_ilload_namespace(self, parent, anamespace_body);
		//namespace xxx { abstract class yyy { ...
	} else if(anamespace_body->tag == ast_abstract_class_decl) {
		class_loader_ilload_abstract_class(self, current, anamespace_body);
		//namespace xxx { class yyy { ...
	} else if (anamespace_body->tag == ast_class_decl) {
		class_loader_ilload_class(self, current, anamespace_body);
		//namespace xxx { interface yyy { ...
	} else if (anamespace_body->tag == ast_interface_decl) {
		class_loader_ilload_interface(self, current, anamespace_body);
		//namespace xxx { enum yyy { ...
	} else if(anamespace_body->tag == ast_enum_decl) {
		class_loader_ilload_enum(self, current, anamespace_body);
		//namespace xxx { any yyy { ...
	} else if (anamespace_body->tag == ast_namespace_member_decl_list) {
		for (int i = 0; i < anamespace_body->vchildren->length; i++) {
			ast* amember = ast_at(anamespace_body, i);
			class_loader_ilload_namespace_body(self, current, parent, amember);
		}
	}
}

static void class_loader_ilload_abstract_class(class_loader* self, il_namespace* current, ast* aclass_decl) {
	assert(aclass_decl->tag == ast_abstract_class_decl);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = true;
}

static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* aclass_decl) {
	assert(aclass_decl->tag == ast_class_decl);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = false;
}

static il_class* class_loader_ilload_classImpl(class_loader* self, il_namespace* current, ast* aclass_decl) {
	ast* atypename = ast_first(aclass_decl);
	ast* aextend_list = ast_second(aclass_decl);
	ast* amember_tree = ast_at(aclass_decl, 2);
	il_class* ilclassz = il_class_new(atypename->u.stringv_value);
	il_type* iltype = il_type_wrap_class(ilclassz);
	//class Foo<A, B>
	CLIL_type_parameter(self, ast_first(atypename), ilclassz->type_parameter_list);
	//class Foo : X, Y 
	CLIL_typename_list(self, ilclassz->extend_list, aextend_list);
	//public:
	//    ....
	//    ....
	if (!ast_is_blank(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	vector_push(current->type_list, iltype);
	return ilclassz;
}

static void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* ainterface_decl) {
	ast* atypename = ast_first(ainterface_decl);
	ast* aextends_list = ast_second(ainterface_decl);
	ast* amember_tree = ast_at(ainterface_decl, 2);
	il_interface* ilinter = il_interface_new(atypename->u.stringv_value);
	il_type* iltype = il_type_wrap_interface(ilinter);
	//interface Foo<A, B>
	CLIL_type_parameter(self, ast_first(atypename), ilinter->type_parameter_list);
	//interface Foo : XXX, YYY, CCC
	CLIL_typename_list(self, ilinter->extends_list, aextends_list);
	//public:
	//    ...
	if (!ast_is_blank(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	vector_push(current->type_list, iltype);
}

static void class_loader_ilload_enum(class_loader * self, il_namespace * current, ast * aenum_decl) {
	assert(aenum_decl->tag == ast_enum_decl);
	ast* aname_list = ast_first(aenum_decl);
	il_enum* ilenum = il_enum_new(aenum_decl->u.stringv_value);
	class_loader_ilload_identifier_list(self, ilenum->item_vec, aname_list);
	vector_push(current->type_list, il_type_wrap_enum(ilenum));
}

static void class_loader_ilload_identifier_list(class_loader * self, vector * list, ast * asource) {
	if (asource->tag == ast_identifier_list) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			class_loader_ilload_identifier_list(self, list, ast_at(asource, i));
		}
	} else if(asource->tag == ast_identifier) {
		string_view str = asource->u.stringv_value;
		vector_push(list, str);
	}
}
