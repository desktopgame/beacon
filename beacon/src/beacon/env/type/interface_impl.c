#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "meta_impl.h"
#include "../generic_type.h"
#include "../type_parameter.h"
#include <stdio.h>
//proto
static void interface_delete_method(vector_item item);
static void interface_type_parameter_delete(vector_item item);
static void interface_generic_type_list_delete(vector_item item);

type * type_wrap_interface(interface_ * self) {
	type* ret = type_new();
	ret->tag = type_interface;
	ret->u.interface_ = self;
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
	return ret;
}

void interface_add_method(interface_ * self, method * m) {
	vector_push(self->method_list, m);
}

method * interface_find_method(interface_ * self, const char * name, vector * args, enviroment * env, il_context* ilctx, int * outIndex) {
	return meta_find_method(self->method_list, name, args, env, ilctx, outIndex);
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
