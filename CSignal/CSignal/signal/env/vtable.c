#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>

vtable * vtable_new() {
	vtable* ret = (vtable*)MEM_MALLOC(sizeof(vtable));
	ret->elements = vector_new();
	ret->proxy = NULL;
	ret->parent = NULL;
	return ret;
}

void vtable_copy(vtable * src, vtable * dst) {
	for (int i = 0; i < src->elements->length; i++) {
		vector_push(dst->elements, vector_at(src->elements, i));
	}
}

void vtable_add(vtable * self, method * m) {
	if (modifier_is_static(m->modifier)) {
		return;
	}
	vector_push(self->elements, m);
}

void vtable_replace(vtable * self, method * m) {
	if (modifier_is_static(m->modifier)) {
		return;
	}
	for (int i = 0; i < self->elements->length; i++) {
		method* e = (method*)vector_at(self->elements, i);
		if (method_equal(m, e)) {
			vector_assign(self->elements, i, m);
			return;
		}
	}
	vector_push(self->elements, m);
}

void vtable_lookup(vtable * self, vtable * castTo) {
	if (self == castTo) {
		return;
	}
	if (self->proxy != NULL) {
		vtable_lookup(self->proxy, castTo);
		return;
	}
	vtable* newVT = vtable_new();
	newVT->parent = self;
	self->proxy = newVT;
	//仮想関数の一覧
	for (int i = 0; i < castTo->elements->length; i++) {
		method* e = (method*)vector_at(castTo->elements, i);
		//具象関数の一覧
		for (int j = 0; j < self->elements->length; j++) {
			//互換性があるなら、
			//具象メソッドを追加
			method* li = (method*)vector_at(self->elements, j);
			if (method_equal(e, li)) {
				vtable_add(newVT, li);
				break;
			}
		}
	}
	assert((newVT->elements->length == castTo->elements->length));
}

vtable * vtable_delegate(vtable * self) {
	if (self->proxy == NULL) {
		return self;
	}
	return vtable_delegate(self->proxy);
}

void vtable_delete(vtable * self) {
	if (self == NULL) {
		return;
	}
	vector_delete(self->elements, vector_deleter_null);
	MEM_FREE(self);
}
