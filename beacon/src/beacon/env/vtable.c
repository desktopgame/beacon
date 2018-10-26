#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

VTable * NewVTable() {
	VTable* ret = (VTable*)MEM_MALLOC(sizeof(VTable));
	ret->elements = NewVector();
	ret->parent = NULL;
	return ret;
}

void CopyVTable(VTable * src, VTable * dst) {
	for (int i = 0; i < src->elements->Length; i++) {
		PushVector(dst->elements, AtVector(src->elements, i));
	}
}

void AddVTable(VTable * self, Method * m) {
	if (IsStaticModifier(m->Modifier)) {
		return;
	}
	PushVector(self->elements, m);
}

void ReplaceVTable(VTable * self, Method * m, CallContext* cctx) {
	if (IsStaticModifier(m->Modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = Ref2Str(m->Name);
	#endif
	for (int i = 0; i < self->elements->Length; i++) {
		Method* e = (Method*)AtVector(self->elements, i);
		//if (IsOverridedMethod(m, e, cctx)) {
		if (IsOverridedMethod(e, m, cctx)) {
			AssignVector(self->elements, i, m);
			return;
		}
	}
	PushVector(self->elements, m);
}

void DeleteVTable(VTable * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->elements, VectorDeleterOfNull);
	MEM_FREE(self);
}
