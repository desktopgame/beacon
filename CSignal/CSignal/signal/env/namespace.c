#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "class.h"
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

namespace_ * namespace_create_at_root(char * name) {
	assert(name != NULL);
	script_context* ctx = script_context_get_current();
	if (ctx->namespaceMap == NULL) {
		ctx->namespaceMap = tree_map_new();
	}
	tree_item item = tree_map_get(ctx->namespaceMap, name);
	if (item == NULL) {
		char* dup = name;//_strdup(name);
		namespace_* newNamespace = namespace_malloc(dup);
		tree_map_put(ctx->namespaceMap, name, newNamespace);
		return newNamespace;
	} else return (namespace_*)item;
}

namespace_ * namespace_get_at_root(char * name) {
	script_context* ctx = script_context_get_current();
	if (ctx->namespaceMap == NULL) {
		return NULL;
	}
	return (namespace_*)tree_map_get(ctx->namespaceMap, name);
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

class_ * namespace_add_class(namespace_ * self, class_ * classz) {
	script_context* ctx = script_context_get_current();
	classz->location = self;
	classz->ref_count++;
	tree_map_put(self->class_map, classz->name, classz);
	classz->absoluteIndex = ctx->class_vec->length;
	vector_push(ctx->class_vec, classz);
	return classz;
}

namespace_ * namespace_get_namespace(namespace_ * self, const char * name) {
	assert(self != NULL);
	assert(name != NULL);
	return (namespace_*)tree_map_get(self->namespace_map, name);
}

class_ * namespace_get_class(namespace_ * self, const char * name) {
	assert(self != NULL);
	assert(name != NULL);

	return (class_*)tree_map_get(self->class_map, name);
}

namespace_ * namespace_signal() {
	return namespace_get_at_root("signal");
}

namespace_ * namespace_lang() {
	return namespace_get_namespace(namespace_signal(), "lang");
}

class_ * namespace_int_class() {
	return namespace_get_class(namespace_lang(), "Int");
}

class_ * namespace_double_class() {
	return namespace_get_class(namespace_lang(), "Double");
}

class_ * namespace_char_class() {
	return namespace_get_class(namespace_lang(), "Char");
}

class_ * namespace_string_class() {
	return namespace_get_class(namespace_lang(), "String");
}

class_ * namespace_void_class() {
	return namespace_get_class(namespace_lang(), "Void");
}

void namespace_dump() {
	script_context* ctx = script_context_get_current();
	if (ctx->namespaceMap == NULL) {
		return;
	}
	namespace_dump_root(ctx->namespaceMap->left, true, 0);
	namespace_dump_root(ctx->namespaceMap->right, true, 0);
}

//private
static namespace_* namespace_malloc(char* name) {
	namespace_* ret = (namespace_*)MEM_MALLOC(sizeof(namespace_));
	ret->class_map = NULL;
	ret->namespace_map = tree_map_new();
	ret->class_map = tree_map_new();
	ret->parent = NULL;
	ret->name = name;//_strdup(name);
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
	printf("%s", root->name);
	text_putline();
	namespace_dump_class(root->class_map, true, depth + 1);
	namespace_dump_root(root->namespace_map, false, depth + 1);
}

static void namespace_put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void namespace_dump_class(tree_map* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->item == NULL)) {
		return;
	}
	if (!isRoot) {

		//namespace_put_indent(depth);
		class_* e = ((class_*)root->item);
		class_dump(e, depth);
		//text_putline();
	}
	namespace_dump_class(root->left, false, depth);
	namespace_dump_class(root->right, false, depth);
}