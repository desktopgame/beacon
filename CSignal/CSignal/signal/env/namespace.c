#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "script_context.h"
#include "../util/text.h"

//static tree_map* tree_map_root = NULL;
//proto
static namespace_* namespace_malloc(char* name);
static void namespace_dump_root(tree_map* root, bool callSelf, int depth);
static void namespace_dump_impl(namespace_* root, int depth);
static void namespace_put_indent(int depth);

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

namespace_ * namespace_get_namespace(namespace_ * self, char * name) {
	assert(self != NULL);
	assert(name != NULL);
	return (namespace_*)tree_map_get(self->namespace_map, name);
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
	namespace_* ret = (namespace_*)malloc(sizeof(namespace_));
	ret->class_map = NULL;
	ret->namespace_map = tree_map_new();
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
	namespace_dump_root(root->namespace_map, false, depth + 1);
}

static void namespace_put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}