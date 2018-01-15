#include "interface_impl.h"
//#include "../type_interface.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include <stdio.h>

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
	return ret;
}

void interface_add_method(interface_ * self, method * m) {
	vector_push(self->method_list, m);
}

void interface_dump(interface_ * self, int depth) {
	text_putindent(depth);
	printf("interface %s", self->name);
	text_putline();
	//継承するインターフェイスの一覧
	for (int i = 0; i < self->impl_list->length; i++) {
		interface_* inter = (interface_*)vector_at(self->impl_list, i);
		text_putindent(depth + 1);
		printf("extend %s", inter->name);
		text_putline();
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
}

void interface_delete(interface_ * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}
