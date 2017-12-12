#include "class_loader.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/io.h"
#include "../parse/parser.h"

//proto
static class_loader* class_loader_new();
static void class_loader_load_impl(class_loader* self, ast* source_code);
static void class_loader_load_import(class_loader* self, ast* import_decl);
static void class_loader_load_namespace(class_loader* self, ast* namespace_decl);
static void class_loader_load_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body);
static void class_loader_load_namespace_body(class_loader* self, ast* namespace_body);
static void class_loader_load_class(class_loader* self, ast* class_decl);

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
	free(self);
}

//private
static class_loader* class_loader_new() {
	class_loader* ret = (class_loader*)malloc(sizeof(class_loader));
	ret->source_code = NULL;
	ret->parent = NULL;
	ret->ref_count = 0;
	ret->type = content_entry_point;
	ret->fail = false;
	return ret;
}

static void class_loader_load_impl(class_loader* self, ast* source_code) {
	for (int i = 0; i < source_code->childCount; i++) {
		ast* child = ast_at(self->source_code, i);
		//import a
		if (child->tag == ast_import_decl) {
			class_loader_load_import(self, child);
		//namespace Foo { ... }
		} else if (child->tag == ast_namespace_decl) {
			class_loader_load_namespace(self, child);
		}
	}
}

static void class_loader_load_import(class_loader* self, ast* import_decl) {
	assert(import_decl->tag == ast_import_decl);
	ast* path = ast_first(import_decl);
	printf("import %s\n", path->u.string_value);
}

static void class_loader_load_namespace(class_loader* self, ast* namespace_decl) {
	assert(namespace_decl->tag == ast_namespace_decl);
	printf("namespace");
	ast* namespace_path = ast_first(namespace_decl);
	ast* namespace_body = ast_second(namespace_decl);
	class_loader_load_namespace_path_recursive(self, namespace_path, namespace_body);
	printf("\n");
	class_loader_load_namespace_body(self, namespace_body);
	printf("\n");
}

static void class_loader_load_namespace_path_recursive(class_loader* self, ast* namespace_path, ast* namespace_body) {
	assert(namespace_path->tag == ast_namespace_path ||
		   namespace_path->tag == ast_namespace_path_list);
	if (namespace_path->tag == ast_namespace_path) {
		printf(" %s", namespace_path->u.string_value);
	} else if (namespace_path->tag == ast_namespace_path_list) {
		for (int i = 0; i < namespace_path->childCount; i++) {
			class_loader_load_namespace_path_recursive(self, ast_at(namespace_path, i), namespace_body);
		}
	}
}

static void class_loader_load_namespace_body(class_loader* self, ast* namespace_body) {
	if (ast_is_blank(namespace_body)) {
		return;
	}
	//assert(namespace_body->tag == ast_namespace_member_decl_list);
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (namespace_body->tag == ast_namespace_decl) {
		class_loader_load_namespace(self, namespace_body);
		//namespace xxx { class yyy { ...
	} else if (namespace_body->tag == ast_class_decl) {
		printf("class decl\n");
		//namespace xxx { any yyy { ...
	} else if (namespace_body->tag == ast_namespace_member_decl_list) {
		for (int i = 0; i < namespace_body->childCount; i++) {
			ast* member = ast_at(namespace_body, i);
			class_loader_load_namespace_body(self, member);
		}
	}
}

static void class_loader_load_class(class_loader* self, ast* class_decl) {

}