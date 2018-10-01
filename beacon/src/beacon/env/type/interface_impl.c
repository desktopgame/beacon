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
Vector* interface_get_generic_interface_treeImpl(interface_* self);
static void interface_delete_method(VectorItem item);
static void interface_DeleteTypeParameter(VectorItem item);
static void interface_generic_type_list_delete(VectorItem item);
static void interface_method_flattenImpl(interface_* self, Vector* dest, int depth);
static void interface_delete_property(VectorItem item);

type * type_wrap_interface(interface_ * self) {
	type* ret = type_new();
	ret->tag = TYPE_INTERFACE_T;
	ret->u.interface_ = self;
	self->parent = ret;
	return ret;
}

interface_ * interface_new(string_view namev) {
	interface_* ret = (interface_*)MEM_MALLOC(sizeof(interface_));
	ret->namev = namev;
	ret->impl_list = NewVector();
	ret->location = NULL;
	ret->method_list = NewVector();
	ret->prop_list = NewVector();
	ret->vt = NULL;
	ret->type_parameter_list = NewVector();
	ret->parent = NULL;
	return ret;
}

void interface_add_method(interface_ * self, method * m) {
	PushVector(self->method_list, m);
}

void interface_add_property(interface_* self, property* p) {
	PushVector(self->prop_list, p);
}

method * interface_ilfind_method(interface_ * self, string_view namev, Vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	return meta_ilfind_method(self->method_list, namev, args, env,cctx, outIndex);
}

method* interface_gfind_method(interface_* self, string_view namev, Vector* gargs, int* outIndex) {
	return meta_gfind_method(self->method_list, namev, gargs, outIndex);
}

Vector* interface_method_flatten_list(Vector* inter_list) {
	Vector* ret = NewVector();
	for(int i=0; i<inter_list->length; i++) {
		interface_* inter = AtVector(inter_list, i);
		//インターフェイスのメソッド一覧を挿入
		Vector* list = interface_method_flatten(inter);
		for(int j=0; j<list->length; j++) {
			PushVector(ret, AtVector(list, j));
		}
		DeleteVector(list, VectorDeleterOfNull);
	}
	return ret;
}

Vector* interface_method_flatten(interface_* self) {
	Vector* ret = NewVector();
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
			vtable_add(self->vt, AtVector(self->method_list, i));
		}
	} else {
		for (int i = 0; i < self->impl_list->length; i++) {
			generic_type* ginter = (generic_type*)AtVector(self->impl_list, i);
			type* cinter = GENERIC2TYPE(ginter);
			interface_* inter = TYPE2INTERFACE(cinter);
//			interface_* inter = (interface_*)AtVector(self->impl_list, i);
			interface_create_vtable(inter);
			vtable_copy(inter->vt, self->vt);
		}
		for (int i = 0; i < self->method_list->length; i++) {
			vtable_add(self->vt, AtVector(self->method_list, i));
		}
	}
}

void interface_unlink(interface_ * self) {
	DeleteVector(self->method_list, interface_delete_method);
	DeleteVector(self->prop_list, interface_delete_property);
	DeleteVector(self->impl_list, VectorDeleterOfNull);
	vtable_delete(self->vt);
}

void interface_delete(interface_ * self) {
	DeleteVector(self->type_parameter_list, interface_DeleteTypeParameter);
	MEM_FREE(self);
}

generic_type* interface_contains(generic_type* source, interface_* find) {
	interface_* self = source->core_type->u.interface_;
	if(self == find) {
		return source;
	}
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* gE = AtVector(self->impl_list, i);
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
	Vector* v = interface_method_flatten(self);
	method* ret = NULL;
	if(v->length == 1) {
		ret = AtVector(v, 0);
	}
	DeleteVector(v, VectorDeleterOfNull);
	return ret;
}


Vector* interface_get_generic_interface_tree(interface_* self) {
	return interface_get_generic_interface_treeImpl(self);
}

generic_type* interface_find_interface(interface_* self, type* tinter) {
	assert(tinter->tag == TYPE_INTERFACE_T);
	if (self == TYPE2INTERFACE(tinter)) {
		return NULL;
	}
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = AtVector(self->impl_list, i);
		if (e->core_type == tinter) {
			return e;
		}
	}
	return NULL;
}

//private
Vector* interface_get_generic_interface_treeImpl(interface_* self) {
	Vector* ret = NewVector();
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* ginter = AtVector(self->impl_list, i);
		PushVector(ret, ginter);
		Vector* inner = interface_get_generic_interface_treeImpl(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		MergeVector(ret, inner);
		DeleteVector(inner, VectorDeleterOfNull);
	}
	return ret;
}
static void interface_delete_method(VectorItem item) {
	method* e = (method*)item;
	DeleteMethod(e);
}

static void interface_DeleteTypeParameter(VectorItem item) {
	type_parameter* e = (type_parameter*)item;
	DeleteTypeParameter(e);
}

static void interface_generic_type_list_delete(VectorItem item) {
	//generic_type* e = (generic_type*)item;
	//generic_type_delete(e);
}

static void interface_method_flattenImpl(interface_* self, Vector* dest, int depth) {
	//tekitou
	#if defined(DEBUG)
	const char* intername = Ref2Str(self->namev);
	#endif
	assert(depth < 42);
	for(int i=0; i<self->method_list->length; i++) {
		method* m = AtVector(self->method_list, i);
		PushVector(dest, m);
	}
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* e = AtVector(self->impl_list, i);
		interface_* inter = TYPE2INTERFACE(e->core_type);
		interface_method_flattenImpl(inter, dest, depth + 1);
	}
}

static void interface_delete_property(VectorItem item) {
	property* e = (property*)item;
	DeleteProperty(e);
}