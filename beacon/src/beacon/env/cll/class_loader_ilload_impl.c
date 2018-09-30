#include "class_loader_ilload_impl.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_TYPE_IMPL.h"
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
static void class_loader_ilload_namespace(class_loader* self, Vector* parent, ast* anamespace_decl);

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
static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, Vector* parent, ast* anamespace_body);

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
static void class_loader_ilload_identifier_list(class_loader* self, Vector* list, ast* asource);

//static il_factor* CLIL_factorImpl(class_loader* self, ast* source);
//static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, ast* source);

void class_loader_ilload_impl(class_loader* self, ast* source_code) {
	assert(self->il_code == NULL);
	self->il_code = NewILToplevel();
	for (int i = 0; i < source_code->vchildren->length; i++) {
		ast* child = AtAST(self->source_code, i);
		//import a
		if (child->tag == AST_IMPORT_DECL_T || child->tag == AST_IMPORT_DECL_LIST_T) {
			class_loader_ilload_import_list(self, child);
		//namespace Foo { ... }
		} else if (child->tag == AST_NAMESPACE_DECL_T) {
			class_loader_ilload_namespace(self, self->il_code->namespace_list, child);
		//print();
		} else if (IsStmtAST(child)) {
			CLIL_body(self, self->il_code->statement_list, child);
		//def f() { ... }
		} else if(child->tag == AST_FUNCTION_DECL_T) {
			class_loader_ilload_function(self, child);
		} else {
			fprintf(stderr, "ast is not collected\n");
			abort();
		}
	}
}

//private
static void class_loader_ilload_function(class_loader * self, ast * asource) {
	assert(asource->tag == AST_FUNCTION_DECL_T);
	ast* afunc_name = AtAST(asource, 0);
	ast* atypeparams = AtAST(asource, 1);
	ast* aparam_list = AtAST(asource, 2);
	ast* afunc_body = AtAST(asource, 3);
	ast* aret_name = AtAST(asource, 4);
	il_function* ilfunc = NewILFunction(afunc_name->u.stringv_value);
	CLIL_type_parameter(self, atypeparams, ilfunc->type_parameter_vec);
	CLIL_parameter_list(self, ilfunc->parameter_list, aparam_list);
	CLIL_body(self, ilfunc->statement_list, afunc_body);
	CLIL_generic_cache(aret_name, ilfunc->return_fqcn);
	PushVector(self->il_code->function_list, ilfunc);
}

static void class_loader_ilload_import_list(class_loader* self, ast* asource) {
	if(asource->tag == AST_IMPORT_DECL_LIST_T) {
		for(int i=0; i<asource->vchildren->length; i++) {
			class_loader_ilload_import_list(self, AtAST(asource, i));
		}
	} else {
		assert(asource->tag == AST_IMPORT_DECL_T);
		class_loader_ilload_import(self, asource);
	}
}

static void class_loader_ilload_import(class_loader* self, ast* aimport_decl) {
	assert(aimport_decl->tag == AST_IMPORT_DECL_T);
	ast* apath = FirstAST(aimport_decl);
	il_import* ret = NewILImport(apath->u.stringv_value);
	PushVector(self->il_code->import_list, ret);
}

static void class_loader_ilload_namespace(class_loader* self, Vector* parent, ast* anamespace_decl) {
	assert(anamespace_decl->tag == AST_NAMESPACE_DECL_T);
	ast* anamespace_path = FirstAST(anamespace_decl);
	ast* anamespace_body = SecondAST(anamespace_decl);
	il_namespace* iln = class_loader_ilload_ast_to_namespace(anamespace_path);
	il_namespace* top = GetRootILNamespace(iln);
	PushVector(parent, top);
	class_loader_ilload_namespace_path_recursive(self, anamespace_path, anamespace_body);
	class_loader_ilload_namespace_body(self, iln, iln->namespace_list, anamespace_body);
}

static void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* anamespace_path, ast* anamespace_body) {
	assert(anamespace_path->tag == AST_NAMESPACE_PATH_T ||
		   anamespace_path->tag == AST_NAMESPACE_PATH_LIST_T);
	if (anamespace_path->tag == AST_NAMESPACE_PATH_T) {
	} else if (anamespace_path->tag == AST_NAMESPACE_PATH_LIST_T) {
		for (int i = 0; i < anamespace_path->vchildren->length; i++) {
			class_loader_ilload_namespace_path_recursive(self, AtAST(anamespace_path, i), anamespace_body);
		}
	}
}

static il_namespace* class_loader_ilload_ast_to_namespace(ast* a) {
	assert(a->tag == AST_NAMESPACE_PATH_T ||
	       a->tag == AST_NAMESPACE_PATH_LIST_T);
	if(a->tag == AST_NAMESPACE_PATH_T) {
		il_namespace* ret = NewILNamespace(a->u.stringv_value);
		return ret;
	} else if(a->tag == AST_NAMESPACE_PATH_LIST_T) {
		ast* al = FirstAST(a);
		ast* ar = SecondAST(a);
		il_namespace* parent = class_loader_ilload_ast_to_namespace(al);
		il_namespace* child = class_loader_ilload_ast_to_namespace(ar);
		child->parent = parent;
		PushVector(parent->namespace_list, child);
		return child;
	}
	return NULL;
}

static void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, Vector* parent, ast* anamespace_body) {
	if (IsBlankAST(anamespace_body)) {
		return;
	}
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (anamespace_body->tag == AST_NAMESPACE_DECL_T) {
		class_loader_ilload_namespace(self, parent, anamespace_body);
		//namespace xxx { abstract class yyy { ...
	} else if(anamespace_body->tag == AST_ABSTRACT_CLASS_DECL_T) {
		class_loader_ilload_abstract_class(self, current, anamespace_body);
		//namespace xxx { class yyy { ...
	} else if (anamespace_body->tag == AST_CLASS_DECL_T) {
		class_loader_ilload_class(self, current, anamespace_body);
		//namespace xxx { interface yyy { ...
	} else if (anamespace_body->tag == AST_INTERFACE_DECL) {
		class_loader_ilload_interface(self, current, anamespace_body);
		//namespace xxx { enum yyy { ...
	} else if(anamespace_body->tag == AST_ENUM_DECL_T) {
		class_loader_ilload_enum(self, current, anamespace_body);
		//namespace xxx { any yyy { ...
	} else if (anamespace_body->tag == AST_NAMESPACE_MEMBER_DECL_LIST_T) {
		for (int i = 0; i < anamespace_body->vchildren->length; i++) {
			ast* amember = AtAST(anamespace_body, i);
			class_loader_ilload_namespace_body(self, current, parent, amember);
		}
	}
}

static void class_loader_ilload_abstract_class(class_loader* self, il_namespace* current, ast* aclass_decl) {
	assert(aclass_decl->tag == AST_ABSTRACT_CLASS_DECL_T);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = true;
}

static void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* aclass_decl) {
	assert(aclass_decl->tag == AST_CLASS_DECL_T);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = false;
}

static il_class* class_loader_ilload_classImpl(class_loader* self, il_namespace* current, ast* aclass_decl) {
	ast* atypename = FirstAST(aclass_decl);
	ast* aextend_list = SecondAST(aclass_decl);
	ast* amember_tree = AtAST(aclass_decl, 2);
	il_class* ilclassz = NewILClass(atypename->u.stringv_value);
	il_type* iltype = WrapILClass(ilclassz);
	//class Foo<A, B>
	CLIL_type_parameter(self, FirstAST(atypename), ilclassz->type_parameter_list);
	//class Foo : X, Y 
	CLIL_typename_list(self, ilclassz->extend_list, aextend_list);
	//public:
	//    ....
	//    ....
	if (!IsBlankAST(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	PushVector(current->type_list, iltype);
	return ilclassz;
}

static void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* ainterface_decl) {
	ast* atypename = FirstAST(ainterface_decl);
	ast* aextends_list = SecondAST(ainterface_decl);
	ast* amember_tree = AtAST(ainterface_decl, 2);
	il_interface* ilinter = NewILInterface(atypename->u.stringv_value);
	il_type* iltype = WrapILInterface(ilinter);
	//interface Foo<A, B>
	CLIL_type_parameter(self, FirstAST(atypename), ilinter->type_parameter_list);
	//interface Foo : XXX, YYY, CCC
	CLIL_typename_list(self, ilinter->extends_list, aextends_list);
	//public:
	//    ...
	if (!IsBlankAST(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	PushVector(current->type_list, iltype);
}

static void class_loader_ilload_enum(class_loader * self, il_namespace * current, ast * aenum_decl) {
	assert(aenum_decl->tag == AST_ENUM_DECL_T);
	ast* aname_list = FirstAST(aenum_decl);
	il_enum* ilenum = NewILEnum(aenum_decl->u.stringv_value);
	class_loader_ilload_identifier_list(self, ilenum->item_vec, aname_list);
	PushVector(current->type_list, WrapILEnum(ilenum));
}

static void class_loader_ilload_identifier_list(class_loader * self, Vector * list, ast * asource) {
	if (asource->tag == AST_IDENTIFIER_LIST_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			class_loader_ilload_identifier_list(self, list, AtAST(asource, i));
		}
	} else if(asource->tag == AST_IDENTIFIER_T) {
		string_view str = asource->u.stringv_value;
		PushVector(list, str);
	}
}
