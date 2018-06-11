#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/generic_type.h"
#include "meta_impl.h"
#include "../generic_type.h"
#include "../type_parameter.h"
#include <stdio.h>
//proto
static void interface_delete_method(vector_item item);
static void interface_type_parameter_delete(vector_item item);
static void interface_generic_type_list_delete(vector_item item);
static void interface_method_flattenImpl(interface_* self, vector* dest, int depth);

type * type_wrap_interface(interface_ * self) {
	type* ret = type_new();
	ret->tag = type_interface;
	ret->u.interface_ = self;
	self->parent = ret;
	return ret;
}

interface_ * interface_new(const char * name) {
	interface_* ret = (interface_*)MEM_MALLOC(sizeof(interface_));
	ret->name = text_strdup(name);
	ret->impl_list = vector_new();
	ret->location = NULL;
	ret->method_list = vector_new();
	ret->vt = NULL;
	ret->type_parameter_list = vector_new();
	ret->parent = NULL;
	return ret;
}

void interface_add_method(interface_ * self, method * m) {
	vector_push(self->method_list, m);
}

method * interface_ilfind_method(interface_ * self, const char * name, vector * args, enviroment * env, int * outIndex) {
	return meta_ilfind_method(self->method_list, name, args, env, outIndex);
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

void interface_dump(interface_ * self, int depth) {
	text_putindent(depth);
	text_printf("interface %s", self->name);
	type_parameter_print(self->type_parameter_list);
	text_putline();
	//継承するインターフェイスの一覧
	for (int i = 0; i < self->impl_list->length; i++) {
		interface_* inter = (interface_*)vector_at(self->impl_list, i);
		text_putindent(depth + 1);
		text_printf("extend %s", inter->name);
		text_putline();
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
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
			interface_* inter = (interface_*)vector_at(self->impl_list, i);
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
	vector_delete(self->impl_list, vector_deleter_null);
	vtable_delete(self->vt);
}

void interface_delete(interface_ * self) {
	vector_delete(self->type_parameter_list, interface_type_parameter_delete);
	MEM_FREE(self->name);
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

//private
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