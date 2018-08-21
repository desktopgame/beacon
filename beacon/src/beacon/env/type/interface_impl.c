#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "../../env/property.h"
#include "../../env/parameter.h"
#include "meta_impl.h"
#include "../generic_type.h"
#include "../type_parameter.h"
#include <stdio.h>
//proto
vector* interface_generic_interface_treeImpl(interface_* self);
static void interface_delete_method(vector_item item);
static void interface_type_parameter_delete(vector_item item);
static void interface_generic_type_list_delete(vector_item item);
static void interface_method_flattenImpl(interface_* self, vector* dest, int depth);
static void interface_delete_property(vector_item item);

type * type_wrap_interface(interface_ * self) {
	type* ret = type_new();
	ret->tag = type_interface_T;
	ret->u.interface_ = self;
	self->parent = ret;
	return ret;
}

interface_ * interface_new(string_view namev) {
	interface_* ret = (interface_*)MEM_MALLOC(sizeof(interface_));
	ret->namev = namev;
	ret->impl_list = vector_new();
	ret->location = NULL;
	ret->method_list = vector_new();
	ret->prop_list = vector_new();
	ret->vt = NULL;
	ret->type_parameter_list = vector_new();
	ret->parent = NULL;
	return ret;
}

void interface_add_method(interface_ * self, method * m) {
	vector_push(self->method_list, m);
}

void interface_add_property(interface_* self, property* p) {
	vector_push(self->prop_list, p);
}

method * interface_ilfind_method(interface_ * self, string_view namev, vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	return meta_ilfind_method(self->method_list, namev, args, env,cctx, outIndex);
}

method* interface_gfind_method(interface_* self, string_view namev, vector* gargs, int* outIndex) {
	return meta_gfind_method(self->method_list, namev, gargs, outIndex);
}

vector* interface_method_flatten_list(vector* inter_list) {
	vector* ret = vector_new();
	for(int i=0; i<inter_list->length; i++) {
		interface_* inter = vector_at(inter_list, i);
		//インターフェイスのメソッド一覧を挿入
		vector* list = interface_method_flatten(inter);
		for(int j=0; j<list->length; j++) {
			vector_push(ret, vector_at(list, j));
		}
		vector_delete(list, vector_deleter_null);
	}
	return ret;
}

vector* interface_method_flatten(interface_* self) {
	vector* ret = vector_new();
	interface_method_flattenImpl(self, ret, 0);
	return ret;
}

void interface_create_vtable(interface_ * self) {
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = vtable_new();
	//他のインターフェイスを継承していないならフラットに並べる
	if (self->impl_list->length == 0) {
		for (int i = 0; i < self->method_list->length; i++) {
			vtable_add(self->vt, vector_at(self->method_list, i));
		}
	} else {
		for (int i = 0; i < self->impl_list->length; i++) {
			generic_type* ginter = (generic_type*)vector_at(self->impl_list, i);
			type* cinter = GENERIC2TYPE(ginter);
			interface_* inter = TYPE2INTERFACE(cinter);
//			interface_* inter = (interface_*)vector_at(self->impl_list, i);
			interface_create_vtable(inter);
			vtable_copy(inter->vt, self->vt);
		}
		for (int i = 0; i < self->method_list->length; i++) {
			vtable_add(self->vt, vector_at(self->method_list, i));
		}
	}
}

void interface_unlink(interface_ * self) {
	vector_delete(self->method_list, interface_delete_method);
	vector_delete(self->prop_list, interface_delete_property);
	vector_delete(self->impl_list, vector_deleter_null);
	vtable_delete(self->vt);
}

void interface_delete(interface_ * self) {
	vector_delete(self->type_parameter_list, interface_type_parameter_delete);
	MEM_FREE(self);
}

generic_type* interface_contains(generic_type* source, interface_* find) {
	interface_* self = source->core_type->u.interface_;
	if(self == find) {
		return source;
	}
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* gE = vector_at(self->impl_list, i);
		if(gE->core_type->u.interface_ == find) {
			return gE;
		}
	}
	return NULL;
}

bool interface_is_functional(interface_* self) {
	return interface_get_function(self) != NULL;
}

method* interface_get_function(interface_* self) {
	vector* v = interface_method_flatten(self);
	method* ret = NULL;
	if(v->length == 1) {
		ret = vector_at(v, 0);
	}
	vector_delete(v, vector_deleter_null);
	return ret;
}


vector* interface_generic_interface_tree(interface_* self) {
	return interface_generic_interface_treeImpl(self);
}

generic_type* interface_find_interface(interface_* self, type* tinter) {
	assert(tinter->tag == type_interface_T);
	if (self == TYPE2INTERFACE(tinter)) {
		return NULL;
	}
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = vector_at(self->impl_list, i);
		if (e->core_type == tinter) {
			return e;
		}
	}
	return NULL;
}

//private
vector* interface_generic_interface_treeImpl(interface_* self) {
	vector* ret = vector_new();
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* ginter = vector_at(self->impl_list, i);
		vector_push(ret, ginter);
		vector* inner = interface_generic_interface_treeImpl(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		vector_merge(ret, inner);
		vector_delete(inner, vector_deleter_null);
	}
	return ret;
}
static void interface_delete_method(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}

static void interface_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}

static void interface_generic_type_list_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}

static void interface_method_flattenImpl(interface_* self, vector* dest, int depth) {
	//tekitou
	#if defined(DEBUG)
	const char* intername = string_pool_ref2str(self->namev);
	#endif
	assert(depth < 42);
	for(int i=0; i<self->method_list->length; i++) {
		method* m = vector_at(self->method_list, i);
		vector_push(dest, m);
	}
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* e = vector_at(self->impl_list, i);
		interface_* inter = TYPE2INTERFACE(e->core_type);
		interface_method_flattenImpl(inter, dest, depth + 1);
	}
}

static void interface_delete_property(vector_item item) {
	property* e = (property*)item;
	property_delete(e);
}