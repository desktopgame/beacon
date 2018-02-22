#include "class_loader_ilload_impl.h"
#include "../il/il_type_interface.h"
#include "../il/il_type_impl.h"
#include "../il/il_field.h"
#include "../il/il_import.h"
#include "../il/il_function.h"
#include "../il/il_method.h"
#include "../il/il_constructor.h"
#include "../il/il_constructor_chain.h"
#include "../il/il_parameter.h"
#include "../il/il_argument.h"
#include "../il/il_stmt_interface.h"
#include "../il/il_stmt_impl.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/logger.h"
#include <stdio.h>
#include <assert.h>
//
//ilload
//
#include"../il/il_type_parameter.h"

//proto
static il_factor* class_loader_ilload_factorImpl(class_loader* self, ast* source);
static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, ast* source);
static void class_loader_ilload_type_parameter(class_loader* self, ast* source, vector* dest);

void class_loader_ilload_impl(class_loader* self, ast* source_code) {
	assert(self->il_code == NULL);
	self->il_code = il_top_level_new();
	for (int i = 0; i < source_code->child_count; i++) {
		ast* child = ast_at(self->source_code, i);
		//import a
		if (child->tag == ast_import_decl) {
			class_loader_ilload_import(self, child);
		//namespace Foo { ... }
		} else if (child->tag == ast_namespace_decl) {
			class_loader_ilload_namespace(self, self->il_code->namespace_list, child);
		//print();
		} else if (child->tag == ast_stmt ||
				   child->tag == ast_stmt_list) {
			class_loader_ilload_body(self, self->il_code->statement_list, child);
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
	class_loader_ilload_parameter_list(self, ilfunc->parameter_list, aparam_list);
	class_loader_ilload_body(self, ilfunc->statement_list, afunc_body);
	class_loader_ilload_fqcn(ast_first(aret_name), ilfunc->return_fqcn);
	vector_push(self->il_code->function_list, ilfunc);
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
	class_loader_ilload_type_parameter(self, ast_first(atypename), ilclassz->type_parameter_list);
	//class Foo : X, Y 
	class_loader_ilload_typename_list(self, ilclassz->extend_list, aextend_list);
	//public:
	//    ....
	//    ....
	if (!ast_is_blank(amember_tree)) {
		class_loader_ilload_member_tree(self, iltype, amember_tree);
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
	class_loader_ilload_type_parameter(self, ast_first(atypename), ilinter->type_parameter_list);
	//interface Foo : XXX, YYY, CCC
	class_loader_ilload_typename_list(self, ilinter->extends_list, aextends_list);
	//public:
	//    ...
	if (!ast_is_blank(amember_tree)) {
		class_loader_ilload_member_tree(self, iltype, amember_tree);
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
		fqcn_cache* e = fqcn_cache_new();
		//[typename [fqcn]]
		class_loader_ilload_fqcn(ast_first(typename_list), e);
		vector_push(dst, e);
	} else if(typename_list->tag == ast_typename_list) {
		for (int i = 0; i < typename_list->child_count; i++) {
			class_loader_ilload_typename_list(self, dst, ast_at(typename_list, i));
		}
	}
}

void class_loader_ilload_member_tree(class_loader* self, il_type* current, ast* tree) {
	if (tree->tag == ast_access_member_tree) {
		for (int i = 0; i < tree->child_count; i++) {
			class_loader_ilload_member_tree(self, current, ast_at(tree, i));
		}
	} else if (tree->tag == ast_access_member_list) {
		ast* access = ast_first(tree);
		ast* member_list = ast_second(tree);
		access_level level = ast_cast_to_access(access);
		class_loader_ilload_member(self, current, member_list, level);
	}
}

void class_loader_ilload_member(class_loader* self, il_type* current, ast* member, access_level level) {
	if(member->tag == ast_member_decl_list) {
		for(int i=0; i<member->child_count; i++) {
			class_loader_ilload_member(self, current, ast_at(member, i), level);
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			class_loader_ilload_field(self, current, child, level);
		} else if (child->tag == ast_method_decl) {
			class_loader_ilload_method(self, current, child, level);
		} else if (child->tag == ast_constructor_decl) {
			class_loader_ilload_constructor(self, current, child, level);
		}
	}
}

void class_loader_ilload_field(class_loader* self, il_type* current, ast* field, access_level level) {
	assert(current->tag == iltype_class);
	ast* modifier = ast_first(field);
	ast* type_name = ast_second(field);
	ast* access_name = ast_at(field, 2);
	il_field* v = il_field_new(access_name->u.string_value);
	class_loader_ilload_fqcn(ast_first(type_name), v->fqcn);
	//v->type = il_type_new(type_name->u.string_value);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	il_type_add_field(current, v);
	//il_class_add_field(current->u.class_, v);
	//vector_push(current->u.class_->field_list, v);
}

void class_loader_ilload_method(class_loader* self, il_type* current, ast* method, access_level level) {
	assert(current->tag == iltype_class || current->tag == iltype_interface);
	ast* modifier = ast_at(method, 0);
	ast* func_name = ast_at(method, 1);
	ast* ageneric = ast_at(method, 2);
	ast* param_list = ast_at(method, 3);
	ast* func_body = ast_at(method, 4);
	ast* ret_name = ast_at(method, 5);
	il_method* v = il_method_new(func_name->u.string_value);
	class_loader_ilload_fqcn(ast_first(ret_name), v->return_fqcn);
//	v->return_type = il_type_new(ret_name->u.string_value);
	v->access = level;
	v->modifier = ast_cast_to_modifier(modifier);
	//TEST((!strcmp(v->name, "main")));
	class_loader_ilload_parameter_list(self, v->parameter_list, param_list);
	class_loader_ilload_body(self, v->statement_list, func_body);
	il_type_add_method(current, v);
	//il_class_add_method(current->u.class_, v);
	//vector_push(il_type_method_vec(current), v);
}

void class_loader_ilload_constructor(class_loader* self, il_type* current, ast* constructor, access_level level) {
	assert(current->tag == iltype_class);
	//ast* amodifier = ast_at(constructor, 0);
	ast* aparams = ast_at(constructor, 0);
	ast* achain = ast_at(constructor, 1);
	ast* abody = ast_at(constructor, 2);
	il_constructor_chain* ilchain = NULL;
	if (!ast_is_blank(achain)) {
		ast* achain_type = ast_first(achain);
		ast* aargs = ast_second(achain);
		ilchain = il_constructor_chain_new();
		ilchain->type = ast_cast_to_chain_type(achain_type);
		class_loader_ilload_argument_list(self, ilchain->argument_list, aargs);
	}
	il_constructor* ilcons = il_constructor_new();
	ilcons->access = level;
	ilcons->chain = ilchain;
	//ilcons->modifier = ast_cast_to_modifier(amodifier);
	class_loader_ilload_parameter_list(self, ilcons->parameter_list, aparams);
	class_loader_ilload_body(self, ilcons->statement_list, abody);
	vector_push(current->u.class_->constructor_list, ilcons);
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

void class_loader_ilload_parameter_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_parameter_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_parameter) {
		ast* type_name = ast_first(source);
		ast* access_name = ast_second(source);
		il_parameter* p = il_parameter_new(access_name->u.string_value);
		class_loader_ilload_fqcn(ast_first(type_name), p->fqcn);
		//p->type = il_type_new(type_name->u.string_value);
		vector_push(list, p);
	}
}

void class_loader_ilload_body(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_stmt_list || source->tag == ast_scope) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_body(self, list, ast_at(source, i));
		}
	} else {
		il_stmt* stmt = class_loader_ilload_bodyImpl(self, source);
		if (stmt != NULL) {
			stmt->lineno = source->lineno;
			vector_push(list, stmt);
		}
	}
}

il_stmt_inferenced_type_init * class_loader_ilload_inferenced_type_init(class_loader * self, ast * source) {
	ast* aname = ast_first(source);
	ast* afact = ast_second(source);
	il_stmt_inferenced_type_init* ret = il_stmt_inferenced_type_init_new(aname->u.string_value);
	ret->fact = class_loader_ilload_factor(self, afact);
	return ret;
}

il_stmt_variable_decl* class_loader_ilload_variable_decl(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aname = ast_second(source);
	il_stmt_variable_decl* ret = il_stmt_variable_decl_new(aname->u.string_value);
	ret->name = text_strdup(aname->u.string_value);
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	return ret;
}

il_stmt_variable_init* class_loader_ilload_variable_init(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aident = ast_second(source);
	ast* afact = ast_at(source, 2);
	il_stmt_variable_init* ret = il_stmt_variable_init_new(aident->u.string_value);
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	ret->fact = class_loader_ilload_factor(self, afact);
	return ret;
}

il_stmt_if* class_loader_ilload_if(class_loader* self, ast* source) {
	assert(source->tag == ast_if);
	il_stmt_if* ret = il_stmt_if_new();
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_factor* ilcond = class_loader_ilload_factor(self, acond);
	//il_stmt_list* ilbody = il_stmt_list_new();
	class_loader_ilload_body(self, ret->body, abody);
	ret->condition = ilcond;
	//ret->body = ilbody;
	return ret;
}

il_stmt_if* class_loader_ilload_if_elif_list(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelif_list = ast_second(source);
	il_stmt_if* ilif = class_loader_ilload_if(self, aif);
	class_loader_ilload_elif_list(self, ilif->elif_list, aelif_list);
	//il_stmt_list_push(list, ilif);
	return ilif;
}

il_stmt_if* class_loader_ilload_if_else(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelse = ast_second(source);
	ast* abody = ast_first(aelse);
	il_stmt_if* ilif = class_loader_ilload_if(self, aif);
	class_loader_ilload_body(self, ilif->else_body->body, abody);
	return ilif;
}

il_stmt_if* class_loader_ilload_if_elif_list_else(class_loader* self, ast* source) {
	ast* aif_eliflist = ast_first(source);
	ast* aelse = ast_second(source);
	il_stmt_if* ilif = class_loader_ilload_if_elif_list(self, aif_eliflist);
	class_loader_ilload_body(self, ilif->else_body->body, ast_first(aelse));
	return ilif;
}

il_stmt_while * class_loader_ilload_while(class_loader * self, ast * source) {
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_stmt_while* ilwhile = il_stmt_while_new();
	ilwhile->condition = class_loader_ilload_factor(self, acond);
	class_loader_ilload_body(self, ilwhile->statement_list, abody);
	return ilwhile;
}

void class_loader_ilload_elif_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_elif_list) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_elif_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_elif) {
		ast* acond = ast_first(source);
		ast* abody = ast_second(source);
		//il_stmt* ilif = il_stmt_if_new();
		il_stmt_elif* ilelif = il_stmt_elif_new();
		ilelif->condition = class_loader_ilload_factor(self, acond);
		class_loader_ilload_body(self, ilelif->body, abody);
		//il_stmt_list_push(list, ilelif);
		il_stmt_elif_list_push(list, ilelif);
	}
}

il_stmt_return* class_loader_ilload_return(class_loader* self, ast* source) {
	assert(source->tag == ast_return);
	ast* afact = ast_first(source);
	il_factor* ilfact = class_loader_ilload_factor(self, afact);
	il_stmt_return* ret = il_stmt_return_new();
	ret->fact = ilfact;
	return ret;
}

il_stmt_try* class_loader_ilload_try(class_loader* self, ast* source) {
	ast* abody = ast_first(source);
	ast* acatch_list = ast_second(source);
	il_stmt_try* ret = il_stmt_try_new();
	class_loader_ilload_body(self, ret->statement_list, abody);
	class_loader_ilload_catch_list(self, ret->catch_list, acatch_list);
	return ret;
}

void class_loader_ilload_catch_list(class_loader* self, vector* dest, ast* source) {
	if(source->tag == ast_stmt_catch) {
		ast* atypename = ast_first(source);
		ast* aname = ast_second(source);
		ast* abody = ast_at(source, 2);
		il_stmt_catch* ilcatch = il_stmt_catch_new(aname->u.string_value);
		class_loader_ilload_fqcn(ast_first(atypename), ilcatch->fqcn);
		class_loader_ilload_body(self, ilcatch->statement_list, abody);
		vector_push(dest, ilcatch);

	} else if(source->tag == ast_stmt_catch_list) {
		for(int i=0; i<source->child_count; i++) {
			class_loader_ilload_catch_list(self, dest, ast_at(source, i));
		}
	}
}

il_stmt_throw* class_loader_ilload_throw(class_loader* self, ast* source) {
	il_stmt_throw* ret = il_stmt_throw_new();
	ret->fact = class_loader_ilload_factor(self, ast_first(source));
	return ret;
}

il_factor* class_loader_ilload_factor(class_loader* self, ast* source) {
	il_factor* ret = class_loader_ilload_factorImpl(self, source);
	ret->lineno = source->lineno;
	return ret;
}

il_factor_bool * class_loader_ilload_true(class_loader * self, ast * source) {
	return il_factor_bool_new(true);
}

il_factor_bool * class_loader_ilload_false(class_loader * self, ast * source) {
	return il_factor_bool_new(false);
}

il_factor_cast * class_loader_ilload_cast(class_loader * self, ast * source) {
	ast* atypename = ast_first(source);
	ast* afact = ast_second(source);
	il_factor_cast* ret = il_factor_cast_new(class_loader_ilload_factor(self, afact));
	class_loader_ilload_fqcn(ast_first(atypename), ret->fqcn);
	return ret;
}

il_factor_unary_op* class_loader_ilload_unary(class_loader* self, ast* source, ilunary_op_type type) {
	il_factor_unary_op* ret = il_factor_unary_op_new(type);
	ast* a = ast_first(source);
	ret->a = class_loader_ilload_factor(self, a);
	return ret;
}

il_factor_binary_op* class_loader_ilload_binary(class_loader* self, ast* source, ilbinary_op_type type) {
	il_factor_binary_op* ret = il_factor_binary_op_new(type);
	ast* aleft = ast_first(source);
	ast* aright = ast_second(source);
	ret->left = class_loader_ilload_factor(self, aleft);
	ret->right = class_loader_ilload_factor(self, aright);
	return ret;
}

il_factor_call* class_loader_ilload_call(class_loader* self, ast* source) {
	assert(source->tag == ast_call);
	ast* aname = ast_first(source);
	ast* aargs = ast_second(source);
	il_factor_call* ilcall = il_factor_call_new(aname->u.string_value);
	class_loader_ilload_argument_list(self, ilcall->argument_list, aargs);
	return ilcall;
}

il_factor_invoke* class_loader_ilload_invoke(class_loader* self, ast* source) {
	assert(source->tag == ast_invoke);
	ast* areceiver = ast_at(source, 0);
	ast* aname = ast_at(source, 1);
	ast* aargs = ast_at(source, 2);
	il_factor_invoke* ilinvoke = il_factor_invoke_new(aname->u.string_value);
	ilinvoke->receiver = class_loader_ilload_factor(self, areceiver);
	class_loader_ilload_argument_list(self, ilinvoke->argument_list, aargs);
	return ilinvoke;
}

il_factor_named_invoke* class_loader_ilload_named_invoke(class_loader* self, ast* source) {
	assert(source->tag == ast_static_invoke);
	ast* afqcn = ast_at(source, 0);
	ast* aname = ast_at(source, 1);
	ast* aargs = ast_at(source, 2);
	il_factor_named_invoke* ret = il_factor_named_invoke_new(aname->u.string_value);
	if (afqcn->tag == ast_fqcn_class_name) {
		ret->fqcn->name = text_strdup(afqcn->u.string_value);
	} else  class_loader_ilload_fqcn(afqcn, ret->fqcn);
	class_loader_ilload_argument_list(self, ret->argument_list, aargs);
	return ret;
}

il_factor_new_instance* class_loader_ilload_new_instance(class_loader* self, ast* source) {
	assert(source->tag == ast_new_instance);
	ast* afqcn = ast_first(source);
	ast* aargs = ast_second(source);
	il_factor_new_instance* ret = il_factor_new_instance_new();
	class_loader_ilload_fqcn(ast_first(afqcn), ret->fqcn);
	class_loader_ilload_argument_list(self, ret->argument_list, aargs);
	return ret;
}

il_factor_field_access* class_loader_ilload_field_access(class_loader* self, ast* source) {
	ast* afact = ast_first(source);
	ast* aident = ast_second(source);
	il_factor_field_access* ret = il_factor_field_access_new(aident->u.string_value);
	ret->fact = class_loader_ilload_factor(self, afact);
	return ret;
}

il_factor_static_field_access* class_loader_ilload_static_field_access(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* aident = ast_second(source);
	il_factor_static_field_access* ret = il_factor_static_field_access_new(aident->u.string_value);
	class_loader_ilload_fqcn(afqcn, ret->fqcn);
	return ret;
}

il_factor_as* class_loader_ilload_as(class_loader* self, ast* source) {
	il_factor_as* ret = il_factor_as_new();
	ret->fact = class_loader_ilload_factor(self, ast_first(source));
	class_loader_ilload_fqcn(ast_first(ast_second(source)), ret->fqcn);
	return ret;
}

il_factor_inc * class_loader_ilload_inc(class_loader * self, ast * source) {
	assert(source->tag == ast_pre_inc ||
		   source->tag == ast_post_inc);
	fix_type type = (source->tag == ast_pre_inc) ? fixtype_pre : fixtype_post;
	il_factor_inc* ret = il_factor_inc_new(type);
	ast* afact = ast_first(source);
	ret->fact = class_loader_ilload_factor(self, afact);
	ret->type = type;
	return ret;
}

il_factor_dec * class_loader_ilload_dec(class_loader * self, ast * source) {
	assert(source->tag == ast_pre_dec ||
		   source->tag == ast_post_dec);
	fix_type type = (source->tag == ast_pre_dec) ? fixtype_pre : fixtype_post;
	il_factor_dec* ret = il_factor_dec_new(type);
	ast* afact = ast_first(source);
	ret->fact = class_loader_ilload_factor(self, afact);
	ret->type = type;
	return ret;
}

void class_loader_ilload_fqcn(ast* fqcn, fqcn_cache* dest) {
	class_loader_ilload_fqcn_impl(fqcn, dest);
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (dest->name == NULL &&
		dest->scope_vec->length > 0) {
		dest->name = (char*)vector_pop(dest->scope_vec);
	}
}

void class_loader_ilload_fqcn_impl(ast* fqcn, fqcn_cache* dest) {
	if (fqcn->tag == ast_fqcn ||
		fqcn->tag == ast_fqcn_part_list) {
		if (fqcn->tag == ast_fqcn_part_list &&
			fqcn->child_count == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			fqcn->tag = ast_fqcn_class_name;
			dest->name = text_strdup(fqcn->u.string_value);
			return;
		}
		for (int i = 0; i < fqcn->child_count; i++) {
			ast* c = ast_at(fqcn, i);
			class_loader_ilload_fqcn_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		vector_push(dest->scope_vec, text_strdup(fqcn->u.string_value));
		fqcn->tag = ast_fqcn_part;
	}
}

void class_loader_ilload_argument_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_argument_list) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_argument_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_argument) {
		ast* primary = ast_first(source);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = class_loader_ilload_factor(self, primary);
		//il_argument_list_push(list, ilarg);
		vector_push(list, ilarg);
	}
}

//private
static il_factor* class_loader_ilload_factorImpl(class_loader* self, ast* source) {
	if (source->tag == ast_int) {
		return il_factor_wrap_int(il_factor_int_new(source->u.int_value));
	} else if (source->tag == ast_double) {
		return il_factor_wrap_double(il_factor_double_new(source->u.double_value));
	} else if (source->tag == ast_char) {
		return il_factor_wrap_char(il_factor_char_new(source->u.char_value));
	} else if (source->tag == ast_string) {
		return il_factor_wrap_string(il_factor_string_new(source->u.string_value));
	} else if (source->tag == ast_call) {
		return il_factor_wrap_call(class_loader_ilload_call(self, source));
	} else if (source->tag == ast_invoke) {
		return il_factor_wrap_invoke(class_loader_ilload_invoke(self, source));
	} else if (source->tag == ast_static_invoke) {
		return il_factor_wrap_named_invoke(class_loader_ilload_named_invoke(self, source));
	} else if (source->tag == ast_variable) {
		return il_factor_wrap_variable(il_factor_variable_new(source->u.string_value));
		//operator(+ - * / %)
	} else if (source->tag == ast_add) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_add));
	} else if (source->tag == ast_sub) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_sub));
	} else if (source->tag == ast_mul) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mul));
	} else if (source->tag == ast_div) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_div));
	} else if (source->tag == ast_mod) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mod));
		//operator(| || & &&)
	} else if (source->tag == ast_bit_or) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_bit_or));
	} else if (source->tag == ast_logic_or) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_logic_or));
	} else if (source->tag == ast_bit_and) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_bit_and));
	} else if (source->tag == ast_logic_and) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_logic_and));
		//operator(== != > >= < <=)
	} else if (source->tag == ast_equal) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_eq));
	} else if (source->tag == ast_notequal) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_noteq));
	} else if (source->tag == ast_gt) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_gt));
	} else if (source->tag == ast_ge) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_ge));
	} else if (source->tag == ast_lt) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_lt));
	} else if (source->tag == ast_le) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_le));
		//operator(= += -= *= /= %=)
	} else if (source->tag == ast_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_assign));
	} else if (source->tag == ast_add_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_add_assign));
	} else if (source->tag == ast_sub_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_sub_assign));
	} else if (source->tag == ast_mul_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mul_assign));
	} else if (source->tag == ast_div_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_div_assign));
	} else if (source->tag == ast_mod_assign) {
		return il_factor_wrap_binary(class_loader_ilload_binary(self, source, ilbinary_mod_assign));
	} else if (source->tag == ast_not) {
		return il_factor_wrap_unary(class_loader_ilload_unary(self, source, ilunary_not));
	} else if (source->tag == ast_neg) {
		return il_factor_wrap_unary(class_loader_ilload_unary(self, source, ilunary_neg));
		//this super
	} else if (source->tag == ast_this) {
		il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
		ret->type = ilfactor_this;
		ret->u.this_ = 0;
		return ret;
	} else if (source->tag == ast_super) {
		il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
		ret->type = ilfactor_super;
		ret->u.super_ = 0;
		return ret;
	} else if (source->tag == ast_new_instance) {
		return il_factor_wrap_new_instance(class_loader_ilload_new_instance(self, source));
	} else if (source->tag == ast_field_access) {
		return il_factor_wrap_field_access(class_loader_ilload_field_access(self, source));
	} else if (source->tag == ast_static_field_access) {
		return il_factor_wrap_static_field_access(class_loader_ilload_static_field_access(self, source));
	} else if (source->tag == ast_cast) {
		return il_factor_wrap_cast(class_loader_ilload_cast(self, source));
	} else if (source->tag == ast_true) {
		return il_factor_wrap_bool(class_loader_ilload_true(self, source));
	} else if (source->tag == ast_false) {
		return il_factor_wrap_bool(class_loader_ilload_false(self, source));
	} else if (source->tag == ast_null) {
		il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
		ret->type = ilfactor_null;
		ret->u.null_ = NULL;
		return ret;
	} else if (source->tag == ast_as) {
		return il_factor_wrap_as(class_loader_ilload_as(self, source));
	} else if (source->tag == ast_pre_inc ||
			   source->tag == ast_post_inc) {
		return il_factor_wrap_inc(class_loader_ilload_inc(self, source));
	} else if (source->tag == ast_pre_dec ||
			   source->tag == ast_post_dec) {
		return il_factor_wrap_dec(class_loader_ilload_dec(self, source));
	}
	return NULL;
}

static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, ast* source) {
	//text_printf("    ");
	//ast_print(source);
	//text_printf("\n");
	switch (source->tag) {
		case ast_stmt:
		{
			return class_loader_ilload_bodyImpl(self, ast_first(source));
		}
		case ast_proc:
		{
			ast* afact = ast_first(source);
			il_factor* ilfact = class_loader_ilload_factor(self, afact);
			il_stmt_proc* ilproc = il_stmt_proc_new();
			ilproc->factor = ilfact;
			assert(ilfact != NULL);
			return il_stmt_wrap_proc(ilproc);
		}
		case ast_stmt_variable_decl:
		{
			il_stmt_variable_decl* ilvardecl = class_loader_ilload_variable_decl(self, source);
			return il_stmt_wrap_variable_decl(ilvardecl);
		}
		case ast_stmt_variable_init:
		{
			il_stmt_variable_init* ilvarinit = class_loader_ilload_variable_init(self, source);
			return il_stmt_wrap_variable_init(ilvarinit);
		}
		case ast_inferenced_type_init:
		{
			il_stmt_inferenced_type_init* ilinfer = class_loader_ilload_inferenced_type_init(self, source);
			return il_stmt_wrap_inferenced_type_init(ilinfer);
		}
		case ast_if:
		{
			il_stmt_if* ilif = class_loader_ilload_if(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list:
		{
			il_stmt_if* ilif = class_loader_ilload_if_elif_list(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_else:
		{
			il_stmt_if* ilif = class_loader_ilload_if_else(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_if_elif_list_else:
		{
			il_stmt_if* ilif = class_loader_ilload_if_elif_list_else(self, source);
			return il_stmt_wrap_if(ilif);
		}
		case ast_while:
		{
			il_stmt_while* ilwh = class_loader_ilload_while(self, source);
			return il_stmt_wrap_while(ilwh);
		}
		case ast_break:
		{
			return il_stmt_wrap_break();
		}
		case ast_continue:
		{
			return il_stmt_wrap_continue();
		}
		case ast_return:
		{
			il_stmt_return* ilret = class_loader_ilload_return(self, source);
			return il_stmt_wrap_return(ilret);
		}
		case ast_stmt_try:
		{
			il_stmt_try* iltry = class_loader_ilload_try(self, source);
			return il_stmt_wrap_try(iltry);
		}
		case ast_stmt_throw:
		{
			il_stmt_throw* ilthrow = class_loader_ilload_throw(self, source);
			return il_stmt_wrap_throw(ilthrow);
		}
		default:
			break;
	}
	return NULL;
}

static void class_loader_ilload_type_parameter(class_loader* self, ast* source, vector* dest) {
	if (ast_is_blank(source)) {
		return;
	}
	if (source->tag == ast_type_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			class_loader_ilload_type_parameter(self, ast_at(source, i), dest);
		}
		return;
	}
	assert(source->tag == ast_type_parameter ||
		   source->tag == ast_type_in_parameter ||
		   source->tag == ast_type_out_parameter);
	il_type_parameter* iltypeparam = il_type_parameter_new(source->u.string_value);
	if (source->tag == ast_type_in_parameter) iltypeparam->kind = il_type_parameter_kind_in;
	if (source->tag == ast_type_out_parameter) iltypeparam->kind = il_type_parameter_kind_out;
	vector_push(dest, iltypeparam);
}