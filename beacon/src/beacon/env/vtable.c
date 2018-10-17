#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

vtable * NewVTable() {
	vtable* ret = (vtable*)MEM_MALLOC(sizeof(vtable));
	ret->elements = NewVector();
	ret->parent = NULL;
	return ret;
}

void CopyVTable(vtable * src, vtable * dst) {
	for (int i = 0; i < src->elements->Length; i++) {
		PushVector(dst->elements, AtVector(src->elements, i));
	}
}

void AddVTable(vtable * self, method * m) {
	if (IsStaticModifier(m->modifier)) {
		return;
	}
	PushVector(self->elements, m);
}

void ReplaceVTable(vtable * self, method * m, call_context* cctx) {
	if (IsStaticModifier(m->modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = Ref2Str(m->namev);
	#endif
	for (int i = 0; i < self->elements->Length; i++) {
		method* e = (method*)AtVector(self->elements, i);
		//if (IsOverridedMethod(m, e, cctx)) {
		if (IsOverridedMethod(e, m, cctx)) {
			AssignVector(self->elements, i, m);
			return;
		}
	}
	PushVector(self->elements, m);
}

void DeleteVTable(vtable * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->elements, VectorDeleterOfNull);
	MEM_FREE(self);
}
