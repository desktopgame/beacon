#include "namespace.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "type_interface.h"
#include "type_impl.h"
#include "script_context.h"
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../util/mem.h"

//static tree_map* tree_map_root = NULL;
//proto
static namespace_* namespace_malloc(string_view namev);

static void namespace_unlink_namespace(vector_item item);
static void namespace_delete_namespace(vector_item item);

static void namespace_unlink_type(vector_item item);
static void namespace_delete_type(vector_item item);
static namespace_* namespace_vfind_namespace(vector* source, string_view namev);
static type* namespace_vfind_type(vector* source, string_view namev);

namespace_ * namespace_create_at_root(string_view namev) {
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_vec == NULL) {
		ctx->namespace_vec = vector_new();
	}
	tree_item item = namespace_vfind_namespace(ctx->namespace_vec, namev);
	if (item == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		vector_push(ctx->namespace_vec, newNamespace);
		return newNamespace;
	} else return (namespace_*)item;
}

namespace_ * namespace_get_at_root(string_view namev) {
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_vec == NULL) {
		return NULL;
	}
	return (namespace_*)namespace_vfind_namespace(ctx->namespace_vec, namev);
}

namespace_ * namespace_add_namespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	namespace_* child = namespace_get_namespace(self, namev);
	if (child == NULL) {
		namespace_* newNamespace = namespace_malloc(namev);
		newNamespace->parent = self;
		child = newNamespace;
		vector_push(self->namespace_vec, child);
		self->ref_count++;
	}
	return child;
}

struct type* namespace_add_type(namespace_* self, type* type) {
	script_context* ctx = script_context_get_current();
	type->location = self;
	vector_push(self->type_vec, type);
	type->absolute_index = ctx->type_vec->length;
	if (type->tag == type_class) {
		type->u.class_->classIndex = type->absolute_index;
	}
	vector_push(ctx->type_vec, type);
	return type;
}

namespace_ * namespace_get_namespace(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return (namespace_*)namespace_vfind_namespace(self->namespace_vec, namev);
}

type * namespace_get_type(namespace_ * self, string_view namev) {
	assert(self != NULL);
	return (type*)namespace_vfind_type(self->type_vec, namev);
}

class_ * namespace_get_class(namespace_ * self, string_view namev) {
	//FIXME:コピペ(namespace_get_interface)
	type* ret = namespace_get_type(self, namev);
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

interface_ * namespace_get_interface(namespace_ * self, string_view namev) {
	//FIXME:コピペ(namespace_get_class)
	type* ret = namespace_get_type(self, namev);
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

namespace_ * namespace_beacon() {
	return namespace_get_at_root(string_pool_intern("beacon"));
}

namespace_ * namespace_lang() {
	return namespace_get_namespace(namespace_beacon(), string_pool_intern("lang"));
}

namespace_* namespace_unsafe() {
	return namespace_get_namespace(namespace_beacon(), string_pool_intern("unsafe"));
}

namespace_* namespace_placeholder() {
	return namespace_get_at_root(string_pool_intern("$placeholder"));
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

void namespace_dump() {
	/*
	script_context* ctx = script_context_get_current();
	if (ctx->namespace_map == NULL) {
		return;
	}
	namespace_dump_root(ctx->namespace_map->left, true, 0);
	namespace_dump_root(ctx->namespace_map->right, true, 0);
	*/
}

void namespace_unlink(namespace_ * self) {
	vector_each(self->namespace_vec, namespace_unlink_namespace);
	vector_each(self->type_vec, namespace_unlink_type);
}

void namespace_delete(namespace_ * self) {
	vector_delete(self->namespace_vec, namespace_delete_namespace);
	vector_delete(self->type_vec, namespace_delete_type);
	MEM_FREE(self);
}

//private
static namespace_* namespace_malloc(string_view namev) {
	namespace_* ret = (namespace_*)MEM_MALLOC(sizeof(namespace_));
	ret->type_vec = NULL;
	ret->namespace_vec = vector_new();
	ret->type_vec = vector_new();
	ret->parent = NULL;
	ret->namev = namev;
	ret->ref_count = 0;
	return ret;
}

static void namespace_unlink_namespace(vector_item item) {
	namespace_* e = (namespace_*)item;
	namespace_unlink(e);
}

static void namespace_delete_namespace(vector_item item) {
	namespace_* e = (namespace_*)item;
	namespace_delete(e);
}

static void namespace_unlink_type(vector_item item) {
	type* e = (type*)item;
	type_unlink(e);
}

static void namespace_delete_type(vector_item item) {
	type* e = (type*)item;
	type_delete(e);
}

static namespace_* namespace_vfind_namespace(vector* source, string_view namev) {
	for(int i=0; i<source->length; i++) {
		namespace_* e = vector_at(source, i);
		if(e->namev == namev) {
			return e;
		}
	}
	return NULL;
}
static type* namespace_vfind_type(vector* source, string_view namev) {
	for(int i=0; i<source->length; i++) {
		type* e = vector_at(source, i);
		if(type_name(e) == namev) {
			return e;
		}
	}
	return NULL;
}