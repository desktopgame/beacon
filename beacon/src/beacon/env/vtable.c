#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

vtable * vtable_new() {
	vtable* ret = (vtable*)MEM_MALLOC(sizeof(vtable));
	ret->elements = NewVector();
	ret->parent = NULL;
	return ret;
}

void vtable_copy(vtable * src, vtable * dst) {
	for (int i = 0; i < src->elements->length; i++) {
		PushVector(dst->elements, AtVector(src->elements, i));
	}
}

void vtable_add(vtable * self, method * m) {
	if (modifier_is_static(m->modifier)) {
		return;
	}
	PushVector(self->elements, m);
}

void vtable_replace(vtable * self, method * m, call_context* cctx) {
	if (modifier_is_static(m->modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = string_pool_ref2str(m->namev);
	#endif
	for (int i = 0; i < self->elements->length; i++) {
		method* e = (method*)AtVector(self->elements, i);
		//if (method_override(m, e, cctx)) {
		if (method_override(e, m, cctx)) {
			AssignVector(self->elements, i, m);
			return;
		}
	}
	PushVector(self->elements, m);
}

void vtable_delete(vtable * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->elements, VectorDeleterOfNull);
	MEM_FREE(self);
}
