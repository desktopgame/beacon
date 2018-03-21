#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "type_interface.h"
#include "type_impl.h"
#include "script_context.h"
#include "../util/text.h"
#include "../util/mem.h"

//static tree_map* tree_map_root = NULL;
//proto
static namespace_* namespace_malloc(char* name);
static void namespace_dump_root(tree_map* root, bool callSelf, int depth);
static void namespace_dump_impl(namespace_* root, int depth);
static void namespace_put_indent(int depth);
static void namespace_dump_class(tree_map* root, bool isRoot, int depth);

static void namespace_unlink_namespace(char* name, tree_item item);
static void namespace_delete_namespace(tree_item item);

static namespace_unlink_type(char* name, tree_item item);
static namespace_delete_type(tree_item item);

namespace_ * namespace_create_at_root(char * name) {
	assert(name != NULL);
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_map == NULL) {
		ctx->namespace_map = tree_map_new();
	}
	tree_item item = tree_map_get(ctx->namespace_map, name);
	if (item == NULL) {
		char* dup = name;//_strdup(name);
		namespace_* newNamespace = namespace_malloc(dup);
		tree_map_put(ctx->namespace_map, name, newNamespace);
		return newNamespace;
	} else return (namespace_*)item;
}

namespace_ * namespace_get_at_root(char * name) {
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_map == NULL) {
		return NULL;
	}
	return (namespace_*)tree_map_get(ctx->namespace_map, name);
}

namespace_ * namespace_add_namespace(namespace_ * self, char * name) {
	assert(self != NULL);
	assert(name != NULL);
	namespace_* child = namespace_get_namespace(self, name);
	if (child == NULL) {
		namespace_* newNamespace = namespace_malloc(name);
		newNamespace->parent = self;
		child = newNamespace;
		tree_map_put(self->namespace_map, name, child);
		self->ref_count++;
	}
	return child;
}

struct type* namespace_add_type(namespace_* self, type* type) {
	script_context* ctx = script_context_get_current();
	type->location = self;
	//classz->ref_count++;
	tree_map_put(self->type_map, type_name(type), type);
	type->absolute_index = ctx->type_vec->length;
	if (type->tag == type_class) {
		type->u.class_->classIndex = type->absolute_index;
	}
	vector_push(ctx->type_vec, type);
	return type;
}

namespace_ * namespace_get_namespace(namespace_ * self, const char * name) {
	assert(self != NULL);
	assert(name != NULL);
	return (namespace_*)tree_map_get(self->namespace_map, name);
}

type * namespace_get_type(namespace_ * self, const char * name) {
	assert(self != NULL);
	assert(name != NULL);
	return (type*)tree_map_get(self->type_map, name);
}

class_ * namespace_get_class(namespace_ * self, const char * name) {
	//FIXME:コピペ(namespace_get_interface)
	type* ret = namespace_get_type(self, name);
	if (ret != NULL && 
		ret->tag != type_class) {
		assert(false);
		return NULL;
	}
	if (ret == NULL) {
		return NULL;
	}
	return ret->u.class_;
}

interface_ * namespace_get_interface(namespace_ * self, const char * name) {
	//FIXME:コピペ(namespace_get_class)
	type* ret = namespace_get_type(self, name);
	if (ret != NULL &&
		ret->tag != type_interface) {
		assert(false);
		return NULL;
	}
	if (ret == NULL) {
		return NULL;
	}
	return ret->u.interface_;
}

namespace_ * namespace_signal() {
	return namespace_get_at_root("signal");
}

namespace_ * namespace_lang() {
	return namespace_get_namespace(namespace_signal(), "lang");
}

type * namespace_object_class() {
	return namespace_get_type(namespace_lang(), "Object");
}

type * namespace_int_class() {
	return namespace_get_type(namespace_lang(), "Int");
}

type * namespace_double_class() {
	return namespace_get_type(namespace_lang(), "Double");
}

type * namespace_char_class() {
	return namespace_get_type(namespace_lang(), "Char");
}

type * namespace_string_class() {
	return namespace_get_type(namespace_lang(), "String");
}

type * namespace_bool_class() {
	return namespace_get_type(namespace_lang(), "Bool");
}

type * namespace_void_class() {
	return namespace_get_type(namespace_lang(), "Void");
}

type * namespace_null_class() {
	return namespace_get_type(namespace_lang(), "Null");
}

void namespace_dump() {
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_map == NULL) {
		return;
	}
	namespace_dump_root(ctx->namespace_map->left, true, 0);
	namespace_dump_root(ctx->namespace_map->right, true, 0);
}

void namespace_unlink(namespace_ * self) {
	tree_map_each(self->namespace_map, namespace_unlink_namespace);
	tree_map_each(self->type_map, namespace_unlink_type);
}

void namespace_delete(namespace_ * self) {
//	text_text_printfln("delete namespace %s", self->name);
	tree_map_delete(self->namespace_map, namespace_delete_namespace);
	tree_map_delete(self->type_map, namespace_delete_type);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static namespace_* namespace_malloc(char* name) {
	namespace_* ret = (namespace_*)MEM_MALLOC(sizeof(namespace_));
	ret->type_map = NULL;
	ret->namespace_map = tree_map_new();
	ret->type_map = tree_map_new();
	ret->parent = NULL;
	ret->name = text_strdup(name);
	ret->ref_count = 0;
	return ret;
}

static void namespace_dump_root(tree_map* root, bool callSelf, int depth) {
	if (root == NULL) {
		return;
	}
	if (callSelf) {
		namespace_dump_impl((namespace_*)root->item, depth);
	}
	if (root->left != NULL) {
		namespace_dump_root(root->left, true, depth);
	}
	if (root->right != NULL) {
		namespace_dump_root(root->right, true, depth);
	}
}

static void namespace_dump_impl(namespace_* root, int depth) {
	namespace_put_indent(depth);
	text_printf("%s", root->name);
	text_putline();
	namespace_dump_class(root->type_map, true, depth + 1);
	namespace_dump_root(root->namespace_map, false, depth + 1);
}

static void namespace_put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		text_printf("    ");
	}
}

static void namespace_dump_class(tree_map* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->item == NULL)) {
		return;
	}
	if (!isRoot) {
		type* e = ((type*)root->item);
		type_dump(e, depth);
	}
	namespace_dump_class(root->left, false, depth);
	namespace_dump_class(root->right, false, depth);
}

static void namespace_unlink_namespace(char* name, tree_item item) {
	namespace_* e = (namespace_*)item;
	//text_printfln("unlink namespace %s", e->name);
	namespace_unlink(e);
}

static void namespace_delete_namespace(tree_item item) {
	namespace_* e = (namespace_*)item;
	//text_printfln("delete namespace %s", e->name);
	namespace_delete(e);
}

static namespace_unlink_type(char* name, tree_item item) {
	type* e = (type*)item;
	//text_printfln("unlink type %s", type_name(e));
	type_unlink(e);
}

static namespace_delete_type(tree_item item) {
	type* e = (type*)item;
	//text_printfln("delete type %s", type_name(e));
	type_delete(e);
}