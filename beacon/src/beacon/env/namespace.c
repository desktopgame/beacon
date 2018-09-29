#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "script_context.h"
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../util/mem.h"

//static tree_map* tree_map_root = NULL;
//proto
static namespace_* namespace_malloc(string_view namev);

static void namespace_unlink_namespace(NumericMapKey key, NumericMapItem item);
static void namespace_delete_namespace(NumericMapKey key, NumericMapItem item);

static void namespace_unlink_type(NumericMapKey key, NumericMapItem item);
static void namespace_delete_type(NumericMapKey key, NumericMapItem item);

static void namespace_dump_root(NumericMap* root, bool callSelf, int depth);
static void namespace_dump_impl(namespace_* root, int depth);
static void namespace_put_indent(int depth);
static void namespace_dump_class(NumericMap* root, bool isRoot, int depth);

namespace_ * namespace_create_at_root(string_view namev) {
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_nmap == NULL) {
		ctx->namespace_nmap = NewNumericMap();
	}
	tree_item item = GetNumericMapValue(ctx->namespace_nmap, namev);
	if (item == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		PutNumericMap(ctx->namespace_nmap, namev, newNamespace);
		return newNamespace;
	} else return (namespace_*)item;
}

namespace_ * namespace_get_at_root(string_view namev) {
	script_context* ctx = script_context_get_current();
	return namespace_get_at_croot(ctx, namev);
}

namespace_* namespace_get_at_croot(script_context* sctx, string_view namev) {
	if (sctx->namespace_nmap == NULL) {
		return NULL;
	}
	return (namespace_*)GetNumericMapValue(sctx->namespace_nmap, namev);
}

namespace_ * namespace_add_namespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	namespace_* child = namespace_get_namespace(self, namev);
	if (child == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		newNamespace->parent = self;
		child = newNamespace;
		PutNumericMap(self->namespace_map, namev, child);
		//PushVector(self->namespace_vec, child);
		self->ref_count++;
	}
	return child;
}

struct type* namespace_add_type(namespace_* self, type* type) {
	script_context* ctx = script_context_get_current();
	type->location = self;
	PutNumericMap(self->type_map, type_name(type), type);
	type->absolute_index = ctx->type_vec->length;
	PushVector(ctx->type_vec, type);
	return type;
}

namespace_ * namespace_get_namespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->namespace_map, namev);
}

type * namespace_get_type(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return GetNumericMapValue(self->type_map, namev);
}

class_ * namespace_get_class(namespace_ * self, string_view namev) {
	return type_as_class(namespace_get_type(self, namev));
}

interface_ * namespace_get_interface(namespace_ * self, string_view namev) {
	return type_as_interface(namespace_get_type(self, namev));
}

namespace_ * namespace_beacon() {
	return namespace_get_at_root(InternString("beacon"));
}

namespace_ * namespace_lang() {
	return namespace_get_namespace(namespace_beacon(), InternString("lang"));
}

namespace_* namespace_unsafe() {
	return namespace_get_namespace(namespace_beacon(), InternString("unsafe"));
}

namespace_* namespace_placeholder() {
	return namespace_get_at_root(InternString("$placeholder"));
}

type * namespace_object_type() {
	return bc_object_type();
}

type * namespace_int_type() {
	return bc_int_type();
}

type * namespace_double_type() {
	return bc_double_type();
}

type * namespace_char_type() {
	return bc_char_type();
}

type * namespace_string_type() {
	return bc_string_type();
}

type * namespace_bool_type() {
	return bc_bool_type();
}

type * namespace_void_type() {
	return bc_void_type();
}

type * namespace_null_type() {
	return bc_null_type();
}

type* namespace_exception_type() {
	return bc_exception_type();
}

void namespace_unlink(namespace_ * self) {
	EachNumericMap(self->namespace_map, namespace_unlink_namespace);
	EachNumericMap(self->type_map, namespace_unlink_type);
}

string_view namespace_tostr(namespace_* self) {
	if(self->parent == NULL) {
		return self->namev;
	}
	return ConcatIntern(
		Ref2Str(ConcatIntern(
			Ref2Str(namespace_tostr(self->parent)),
			InternString("::")
		)),
		self->namev
	);
}

void namespace_delete(namespace_ * self) {
	DeleteNumericMap(self->namespace_map, namespace_delete_namespace);
	DeleteNumericMap(self->type_map, namespace_delete_type);
	MEM_FREE(self);
}

//private
static namespace_* namespace_malloc(string_view namev) {
	namespace_* ret = (namespace_*)MEM_MALLOC(sizeof(namespace_));
	ret->namespace_map = NewNumericMap();
	ret->type_map = NewNumericMap();
	ret->parent = NULL;
	ret->namev = namev;
	ret->ref_count = 0;
	return ret;
}

static void namespace_unlink_namespace(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	namespace_unlink(e);
}

static void namespace_delete_namespace(NumericMapKey key, NumericMapItem item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}

static void namespace_unlink_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	type_unlink(e);
}

static void namespace_delete_type(NumericMapKey key, NumericMapItem item) {
	type* e = (type*)item;
	type_delete(e);
}

static void namespace_dump_root(NumericMap* root, bool callSelf, int depth) {
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
	printf("%s", Ref2Str(root->namev));
	Println();
	namespace_dump_class(root->type_map, true, depth + 1);
	namespace_dump_root(root->namespace_map, false, depth + 1);
}

static void namespace_put_indent(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}

static void namespace_dump_class(NumericMap* root, bool isRoot, int depth) {
	if (!isRoot && (root == NULL || root->item == NULL)) {
		return;
	}
	if (!isRoot) {
		type* e = ((type*)root->item);
		//type_dump(e, depth);
		assert(false);
	}
	namespace_dump_class(root->left, false, depth);
	namespace_dump_class(root->right, false, depth);
}