#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/io.h"
#include "../parse/parser.h"
#include "../il/il_class.h"
#include "../il/il_field.h"
#include "../il/il_field_list.h"
#include "../il/il_method.h"
#include "../il/il_method_list.h"
#include "../il/il_stmt_impl.h"
#include "../il/il_factor_impl.h"

//proto
static class_loader* class_loader_new();
static void class_loader_load_impl(class_loader* self, ast* source_code);
static void class_loader_load_import(class_loader* self, ast* import_decl);
static void class_loader_load_namespace(class_loader* self, il_namespace_list* parent, ast* namespace_decl);
static void class_loader_load_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);
static il_namespace* class_loader_load_ast_to_namespace(ast* a);
static void class_loader_load_namespace_body(class_loader* self, il_namespace* current, il_namespace_list* parent, ast* namespace_body);
static void class_loader_load_class(class_loader* self, il_namespace* current, ast* class_decl);
static void class_loader_load_member(class_loader* self, il_class* current, ast* member);
static void class_loader_load_field(class_loader* self, il_class* current, ast* field);
static void class_loader_load_method(class_loader* self, il_class* current, ast* method);
static void class_loader_load_param(class_loader* self, il_parameter_list* list, ast* source);
static void class_loader_load_body(class_loader* self, il_stmt_list* list, ast* source);
static il_stmt_if* class_loader_load_if(class_loader* self, ast* source);
static il_stmt_if* class_loader_load_if_elif_list(class_loader* self, ast* source);
static void class_loader_load_elif_list(class_loader* self, il_stmt_elif_list* list, ast* source);
static il_stmt_if* class_loader_load_if_else(class_loader* self, ast* source);
static il_stmt_if* class_loader_load_if_elif_list_else(class_loader* self, ast* source);
static il_factor* class_loader_load_factor(class_loader* self, ast* source);
static void class_loader_load_constructor(class_loader* self, il_class* current, ast* constructor);

class_loader * class_loader_new_entry_point(const char * filename) {
	class_loader* cll = class_loader_new();
	char* text = io_read_text(filename);
	parser* p = parser_parse_from_source(text);
	//解析に失敗した場合
	if (p->fail) {
		cll->fail = true;
		free(text);
		parser_pop();
		return cll;
	}
	cll->source_code = p->root;
	p->root = NULL;
	free(text);
	parser_pop();
	return cll;
}

void class_loader_load(class_loader * self) {
	assert(self != NULL);
	assert(self->source_code != NULL);
	system("cls");
	ast_print_tree(self->source_code);
	class_loader_load_impl(self, self->source_code);
}

void class_loader_delete(class_loader * self) {
	assert(self != NULL);
	assert(self->ref_count == 0);
	if (self->parent != NULL) {
		self->parent->ref_count--;
	}
	//free(self->source_code);
	ast_delete(self->source_code);
	il_top_level_delete(self->il_code);
	free(self);
}

//private
static class_loader* class_loader_new() {
	class_loader* ret = (class_loader*)malloc(sizeof(class_loader));
	ret->source_code = NULL;
	ret->il_code = NULL;
	ret->parent = NULL;
	ret->ref_count = 0;
	ret->type = content_entry_point;
	ret->fail = false;
	return ret;
}

static void class_loader_load_impl(class_loader* self, ast* source_code) {
	self->il_code = il_top_level_new();
	for (int i = 0; i < source_code->childCount; i++) {
		ast* child = ast_at(self->source_code, i);
		//import a
		if (child->tag == ast_import_decl) {
			class_loader_load_import(self, child);
		//namespace Foo { ... }
		} else if (child->tag == ast_namespace_decl) {
			class_loader_load_namespace(self, self->il_code->namespace_list, child);
		}
	}
	il_top_level_dump(self->il_code, 0);
}

static void class_loader_load_import(class_loader* self, ast* import_decl) {
	assert(import_decl->tag == ast_import_decl);
	ast* path = ast_first(import_decl);
	il_import_list_push(self->il_code->import_list, il_import_new(path->u.string_value));
	printf("import %s\n", path->u.string_value);
}

static void class_loader_load_namespace(class_loader* self, il_namespace_list* parent, ast* namespace_decl) {
	assert(namespace_decl->tag == ast_namespace_decl);
	//printf("namespace");
	ast* namespace_path = ast_first(namespace_decl);
	ast* namespace_body = ast_second(namespace_decl);
	il_namespace* iln = class_loader_load_ast_to_namespace(namespace_path);
	il_namespace* top = il_namespace_root(iln);
	//printf("%s", top->name);
	il_namespace_list_push(parent, top);
	class_loader_load_namespace_path_recursive(self, namespace_path, namespace_body);
	//printf("\n");
	class_loader_load_namespace_body(self, iln, iln->namespace_list, namespace_body);
	//printf("\n");
}

static void class_loader_load_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body) {
	assert(namespace_path->tag == ast_namespace_path ||
		   namespace_path->tag == ast_namespace_path_list);
	if (namespace_path->tag == ast_namespace_path) {
	//	printf(" %s", namespace_path->u.string_value);
	} else if (namespace_path->tag == ast_namespace_path_list) {
		for (int i = 0; i < namespace_path->childCount; i++) {
			class_loader_load_namespace_path_recursive(self, ast_at(namespace_path, i), namespace_body);
		}
	}
}

static il_namespace* class_loader_load_ast_to_namespace(ast* a) {
	assert(a->tag == ast_namespace_path ||
	       a->tag == ast_namespace_path_list);
	if(a->tag == ast_namespace_path) {
		printf("-  %s", a->u.string_value);
		text_putline();
		il_namespace* ret = il_namespace_new(a->u.string_value);
		return ret;
	} else if(a->tag == ast_namespace_path_list) {
		ast* l = ast_first(a);
		ast* r = ast_second(a);
		il_namespace* parent = class_loader_load_ast_to_namespace(l);
		il_namespace* child = class_loader_load_ast_to_namespace(r);
		child->parent = parent;
		il_namespace_list_push(parent->namespace_list, child);
		return child;
	}
}

static void class_loader_load_namespace_body(class_loader* self, il_namespace* current, il_namespace_list* parent, ast* namespace_body) {
	if (ast_is_blank(namespace_body)) {
		return;
	}
	//assert(namespace_body->tag == ast_namespace_member_decl_list);
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (namespace_body->tag == ast_namespace_decl) {
		class_loader_load_namespace(self, parent, namespace_body);
		//namespace xxx { class yyy { ...
	} else if (namespace_body->tag == ast_class_decl) {
		//printf("class decl\n");
		class_loader_load_class(self, current, namespace_body);
		//namespace xxx { any yyy { ...
	} else if (namespace_body->tag == ast_namespace_member_decl_list) {
		for (int i = 0; i < namespace_body->childCount; i++) {
			ast* member = ast_at(namespace_body, i);
			class_loader_load_namespace_body(self, current, parent, member);
		}
	}
}

static void class_loader_load_class(class_loader* self, il_namespace* current, ast* class_decl) {
	ast* super_class = ast_first(class_decl);
	ast* member_list = ast_second(class_decl);
	il_class* classz = il_class_new(class_decl->u.string_value);
	//親クラスが宣言されていない
	if(ast_is_blank(super_class)) {
		classz->super = NULL;
	} else {
		classz->super = il_type_new(super_class->u.string_value);
	}
	class_loader_load_member(self, classz, member_list);
	il_class_list_push(current->class_list, classz);
}

static void class_loader_load_member(class_loader* self, il_class* current, ast* member) {
	if(member->tag == ast_member_decl_list) {
		for(int i=0; i<member->childCount; i++) {
			class_loader_load_member(self, current, ast_at(member, i));
		}
	} else if(member->tag == ast_member_decl) {
		ast* child = ast_first(member);
		if (child->tag == ast_field_decl) {
			class_loader_load_field(self, current, child);
		} else if (child->tag == ast_func_decl) {
			class_loader_load_method(self, current, child);
		} else if (child->tag == ast_constructor_decl) {
			class_loader_load_constructor(self, current, child);
		}
	}
}

static void class_loader_load_field(class_loader* self, il_class* current, ast* field) {
	ast* type_name = ast_first(field);
	ast* access_name = ast_second(field);
	il_field* v = il_field_new(access_name->u.string_value);
	v->type = il_type_new(type_name->u.string_value);
	il_field_list_push(current->field_list, v);
}

static void class_loader_load_method(class_loader* self, il_class* current, ast* method) {
	ast* func_name = ast_at(method, 0);
	ast* param_list = ast_at(method, 1);
	ast* func_body = ast_at(method, 2);
	ast* ret_name = ast_at(method, 3);
	il_method* v = il_method_new(func_name->u.string_value);
	v->return_type = il_type_new(ret_name->u.string_value);
	class_loader_load_param(self, v->parameter_list, param_list);
	class_loader_load_body(self, v->statement_list, func_body);
	il_method_list_push(current->method_list, v);
}

static void class_loader_load_param(class_loader* self, il_parameter_list* list, ast* source) {
	if (source->tag == ast_parameter_list) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_load_param(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_parameter) {
		ast* type_name = ast_first(source);
		ast* access_name = ast_second(source);
		il_parameter* p = il_parameter_new(access_name->u.string_value);
		p->type = il_type_new(type_name->u.string_value);
		il_parameter_list_push(list, p);
	}
}

static void class_loader_load_body(class_loader* self, il_stmt_list* list, ast* source) {
	if (source->tag == ast_stmt_list || source->tag == ast_scope) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_load_body(self, list, ast_at(source, i));
		}
	} else {
		printf("    ");
		ast_print(source);
		printf("\n");
		switch (source->tag) {
			case ast_stmt:
			{
				class_loader_load_body(self, list, ast_first(source));
				break;
			}
			case ast_if:
			{
				il_stmt_if* ilif = class_loader_load_if(self, source);
				il_stmt_list_push(list, il_wrap_if(ilif));
				break;
			}
			case ast_if_elif_list:
			{
				il_stmt* ilif = class_loader_load_if_elif_list(self, source);
				il_stmt_list_push(list, il_wrap_if(ilif));
				break;
			}
			case ast_if_else:
			{
				il_stmt* ilif = class_loader_load_if_else(self, source);
				il_stmt_list_push(list, il_wrap_if(ilif));
				break;
			}
			case ast_if_elif_list_else:
			{
				il_stmt_if* ilif = class_loader_load_if_elif_list_else(self, source);
				il_stmt_list_push(list, il_wrap_if(ilif));
				break;
			}
			default:
				break;
		}
	}
}

static il_stmt_if* class_loader_load_if(class_loader* self, ast* source) {
	assert(source->tag == ast_if);
	il_stmt_if* ret = il_stmt_if_new();
	ast* acond = ast_first(source);
	ast* abody = ast_second(source);
	il_factor* ilcond = class_loader_load_factor(self, acond);
	il_stmt_list* ilbody = il_stmt_list_new();
	class_loader_load_body(self, ilbody, abody);
	ret->condition = ilcond;
	ret->body = ilbody;
	return ret;
}

static il_stmt_if* class_loader_load_if_elif_list(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelif_list = ast_second(source);
	il_stmt_if* ilif = class_loader_load_if(self, aif);
	class_loader_load_elif_list(self, ilif->elif_list, aelif_list);
	//il_stmt_list_push(list, ilif);
	return ilif;
}

static il_stmt_if* class_loader_load_if_else(class_loader* self, ast* source) {
	ast* aif = ast_first(source);
	ast* aelse = ast_second(source);
	ast* abody = ast_first(aelse);
	il_stmt_if* ilif = class_loader_load_if(self, aif);
	class_loader_load_body(self, ilif->else_body, abody);
	return ilif;
}

static il_stmt_if* class_loader_load_if_elif_list_else(class_loader* self, ast* source) {
	ast* aif_eliflist = ast_first(source);
	ast* aelse = ast_second(source);
	il_stmt_if* ilif = class_loader_load_if_elif_list(self, aif_eliflist);
	class_loader_load_body(self, ilif->else_body, ast_first(aelse));
	return ilif;
}

static void class_loader_load_elif_list(class_loader* self, il_stmt_elif_list* list, ast* source) {
	if (source->tag == ast_elif_list) {
		for (int i = 0; i < source->childCount; i++) {
			class_loader_load_elif_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_elif) {
		ast* acond = ast_first(source);
		ast* abody = ast_second(source);
		//il_stmt* ilif = il_stmt_if_new();
		il_stmt_elif* ilelif = il_stmt_elif_new();
		ilelif->condition = class_loader_load_factor(self, acond);
		class_loader_load_body(self, ilelif->body, abody);
		//il_stmt_list_push(list, ilelif);
		il_stmt_elif_list_push(list, ilelif);
	}
}

static il_factor* class_loader_load_factor(class_loader* self, ast* source) {
	if (source->tag == ast_int) {
		return il_factor_int_new(source->u.int_value);
	} else if (source->tag == ast_double) {
		return il_factor_double_new(source->u.double_value);
	} else if (source->tag == ast_char) {
		return il_factor_char_new(source->u.char_value);
	} else if (source->tag == ast_string) {
		return il_factor_string_new(source->u.string_value);
	}
	return NULL;
}

static void class_loader_load_constructor(class_loader* self, il_class* current, ast* constructor) {
}