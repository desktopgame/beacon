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
#include "../../util/xassert.h"
#include "../../util/logger.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
//
//ilload
//
#include "../../il/il_type_parameter.h"
#include "../../il/il_type_parameter_rule.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_member_module_impl.h"

//proto
static il_factor* CLIL_factorImpl(class_loader* self, ast* source);
static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, ast* source);

void class_loader_ilload_impl(class_loader* self, ast* source_code) {
	assert(self->il_code == NULL);
	self->il_code = il_top_level_new();
	for (int i = 0; i < source_code->child_count; i++) {
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
			text_putline();
		}
	}
	//il_top_level_dump(self->il_code, 0);
}

void class_loader_ilload_function(class_loader * self, ast * source) {
	assert(source->tag == ast_function_decl);
	ast* afunc_name = ast_at(source, 0);
	ast* aparam_list = ast_at(source, 1);
	ast* afunc_body = ast_at(source, 2);
	ast* aret_name = ast_at(source, 3);
	il_function* ilfunc = il_function_new(afunc_name->u.string_value);
	CLIL_parameter_list(self, ilfunc->parameter_list, aparam_list);
	CLIL_body(self, ilfunc->statement_list, afunc_body);
	CLIL_generic_cache(ast_first(aret_name), ilfunc->return_fqcn);
	vector_push(self->il_code->function_list, ilfunc);
}

void class_loader_ilload_import_list(class_loader* self, ast* source) {
	if(source->tag == ast_import_decl_list) {
		for(int i=0; i<source->child_count; i++) {
			class_loader_ilload_import_list(self, ast_at(source, i));
		}
	} else {
		assert(source->tag == ast_import_decl);
		class_loader_ilload_import(self, source);
	}
}

void class_loader_ilload_import(class_loader* self, ast* import_decl) {
	assert(import_decl->tag == ast_import_decl);
	ast* path = ast_first(import_decl);
	il_import* ret = il_import_new(path->u.string_value);
	vector_push(self->il_code->import_list, (vector_item)ret);
	//text_printf("import %s\n", path->u.string_value);
}

void class_loader_ilload_namespace(class_loader* self, vector* parent, ast* namespace_decl) {
	assert(namespace_decl->tag == ast_namespace_decl);
	//text_printf("namespace");
	ast* namespace_path = ast_first(namespace_decl);
	ast* namespace_body = ast_second(namespace_decl);
	il_namespace* iln = class_loader_ilload_ast_to_namespace(namespace_path);
	il_namespace* top = il_namespace_root(iln);
	//text_printf("%s", top->name);
	vector_push(parent, top);
	class_loader_ilload_namespace_path_recursive(self, namespace_path, namespace_body);
	//text_printf("\n");
	class_loader_ilload_namespace_body(self, iln, iln->namespace_list, namespace_body);
	//text_printf("\n");
}

void class_loader_ilload_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body) {
	assert(namespace_path->tag == ast_namespace_path ||
		   namespace_path->tag == ast_namespace_path_list);
	if (namespace_path->tag == ast_namespace_path) {
	//	text_printf(" %s", namespace_path->u.string_value);
	} else if (namespace_path->tag == ast_namespace_path_list) {
		for (int i = 0; i < namespace_path->child_count; i++) {
			class_loader_ilload_namespace_path_recursive(self, ast_at(namespace_path, i), namespace_body);
		}
	}
}

il_namespace* class_loader_ilload_ast_to_namespace(ast* a) {
	assert(a->tag == ast_namespace_path ||
	       a->tag == ast_namespace_path_list);
	if(a->tag == ast_namespace_path) {
		//text_printf("-  %s", a->u.string_value);
		//text_putline();
		il_namespace* ret = il_namespace_new(a->u.string_value);
		return ret;
	} else if(a->tag == ast_namespace_path_list) {
		ast* l = ast_first(a);
		ast* r = ast_second(a);
		il_namespace* parent = class_loader_ilload_ast_to_namespace(l);
		il_namespace* child = class_loader_ilload_ast_to_namespace(r);
		child->parent = parent;
		vector_push(parent->namespace_list, child);
		return child;
	}
	ERROR("unsupported tag");
	return NULL;
}

void class_loader_ilload_namespace_body(class_loader* self, il_namespace* current, vector* parent, ast* namespace_body) {
	if (ast_is_blank(namespace_body)) {
		return;
	}
	//assert(namespace_body->tag == ast_namespace_member_decl_list);
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (namespace_body->tag == ast_namespace_decl) {
		class_loader_ilload_namespace(self, parent, namespace_body);
		//namespace xxx { class yyy { ...
	} else if (namespace_body->tag == ast_class_decl) {
		//text_printf("class decl\n");
		class_loader_ilload_class(self, current, namespace_body);
		//namespace xxx { interface yyy { ...
	} else if (namespace_body->tag == ast_interface_decl) {
		class_loader_ilload_interface(self, current, namespace_body);
		//namespace xxx { enum yyy { ...
	} else if(namespace_body->tag == ast_enum_decl) {
		class_loader_ilload_enum(self, current, namespace_body);
		//namespace xxx { any yyy { ...
	} else if (namespace_body->tag == ast_namespace_member_decl_list) {
		for (int i = 0; i < namespace_body->child_count; i++) {
			ast* member = ast_at(namespace_body, i);
			class_loader_ilload_namespace_body(self, current, parent, member);
		}
	}
}

void class_loader_ilload_class(class_loader* self, il_namespace* current, ast* class_decl) {
	assert(class_decl->tag == ast_class_decl);
	ast* atypename = ast_first(class_decl);
	ast* aextend_list = ast_second(class_decl);
	ast* amember_tree = ast_at(class_decl, 2);
	il_class* ilclassz = il_class_new(atypename->u.string_value);
	il_type* iltype = il_type_wrap_class(ilclassz);
	//class Foo<A, B>
	CLIL_type_parameter(self, ast_first(atypename), ilclassz->type_parameter_list);
	//class Foo : X, Y 
	class_loader_ilload_typename_list(self, ilclassz->extend_list, aextend_list);
	//public:
	//    ....
	//    ....
	if (!ast_is_blank(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	vector_push(current->type_list, iltype);
	//il_namespace_add_entity(current, classz);
	//vector_push(current->class_list, classz);
}

void class_loader_ilload_interface(class_loader* self, il_namespace* current, ast* interface_decl) {
	ast* atypename = ast_first(interface_decl);
	ast* aextends_list = ast_second(interface_decl);
	ast* amember_tree = ast_at(interface_decl, 2);
	il_interface* ilinter = il_interface_new(atypename->u.string_value);
	il_type* iltype = il_type_wrap_interface(ilinter);
	//interface Foo<A, B>
	CLIL_type_parameter(self, ast_first(atypename), ilinter->type_parameter_list);
	//interface Foo : XXX, YYY, CCC
	class_loader_ilload_typename_list(self, ilinter->extends_list, aextends_list);
	//public:
	//    ...
	if (!ast_is_blank(amember_tree)) {
		CLIL_member_tree(self, iltype, amember_tree);
	}
	vector_push(current->type_list, iltype);
}

void class_loader_ilload_enum(class_loader * self, il_namespace * current, ast * enum_decl) {
	assert(enum_decl->tag == ast_enum_decl);
	ast* aname_list = ast_first(enum_decl);
	il_enum* ilenum = il_enum_new(enum_decl->u.string_value);
	class_loader_ilload_identifier_list(self, ilenum->item_vec, aname_list);
	vector_push(current->type_list, il_type_wrap_enum(ilenum));
}

void class_loader_ilload_typename_list(class_loader * self, vector * dst, ast * typename_list) {
	if (ast_is_blank(typename_list)) {
		return;
	}
	if (typename_list->tag == ast_typename) {
		//fqcn_cache* e = fqcn_cache_new();
		generic_cache* e = generic_cache_new();
		//[typename [fqcn]]
		CLIL_generic_cache(typename_list, e);
		vector_push(dst, e);
	} else if(typename_list->tag == ast_typename_list) {
		for (int i = 0; i < typename_list->child_count; i++) {
			class_loader_ilload_typename_list(self, dst, ast_at(typename_list, i));
		}
	}
}

void class_loader_ilload_identifier_list(class_loader * self, vector * list, ast * source) {
	if (source->tag == ast_identifier_list) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_identifier_list(self, list, ast_at(source, i));
		}
	} else if(source->tag == ast_identifier) {
		char* str = source->u.string_value;
		vector_push(list, str);
	}
}
