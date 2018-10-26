#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

VTable * NewVTable() {
	VTable* ret = (VTable*)MEM_MALLOC(sizeof(VTable));
	ret->Elements = NewVector();
	ret->Parent = NULL;
	return ret;
}

void CopyVTable(VTable * src, VTable * dst) {
	for (int i = 0; i < src->Elements->Length; i++) {
		PushVector(dst->Elements, AtVector(src->Elements, i));
	}
}

void AddVTable(VTable * self, Method * m) {
	if (IsStaticModifier(m->Modifier)) {
		return;
	}
	PushVector(self->Elements, m);
}

void ReplaceVTable(VTable * self, Method * m, CallContext* cctx) {
	if (IsStaticModifier(m->Modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = Ref2Str(m->Name);
	#endif
	for (int i = 0; i < self->Elements->Length; i++) {
		Method* e = (Method*)AtVector(self->Elements, i);
		//if (IsOverridedMethod(m, e, cctx)) {
		if (IsOverridedMethod(e, m, cctx)) {
			AssignVector(self->Elements, i, m);
			return;
		}
	}
	PushVector(self->Elements, m);
}

void DeleteVTable(VTable * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->Elements, VectorDeleterOfNull);
	MEM_FREE(self);
}
