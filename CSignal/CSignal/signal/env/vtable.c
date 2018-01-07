#include "vtable.h"
#include "../util/mem.h"
#include "method.h"

vtable * vtable_new() {
	vtable* ret = (vtable*)MEM_MALLOC(sizeof(vtable));
	ret->elements = vector_new();
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

void vtable_delete(vtable * self) {
	vector_delete(self->elements, vector_deleter_null);
	MEM_FREE(self);
}
