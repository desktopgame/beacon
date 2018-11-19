#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

bc_VTable * bc_NewVTable() {
	bc_VTable* ret = (bc_VTable*)MEM_MALLOC(sizeof(bc_VTable));
	ret->Elements = NewVector();
	ret->Parent = NULL;
	return ret;
}

void bc_CopyVTable(bc_VTable * src, bc_VTable * dst) {
	for (int i = 0; i < src->Elements->Length; i++) {
		PushVector(dst->Elements, AtVector(src->Elements, i));
	}
}

void bc_AddVTable(bc_VTable * self, bc_Method * m) {
	if (bc_IsStaticModifier(m->Modifier)) {
		return;
	}
	PushVector(self->Elements, m);
}

void bc_ReplaceVTable(bc_VTable * self, bc_Method * m, CallContext* cctx) {
	if (bc_IsStaticModifier(m->Modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = Ref2Str(m->Name);
	#endif
	for (int i = 0; i < self->Elements->Length; i++) {
		bc_Method* e = (bc_Method*)AtVector(self->Elements, i);
		//if (IsOverridedMethod(m, e, cctx)) {
		if (bc_IsOverridedMethod(e, m, cctx)) {
			AssignVector(self->Elements, i, m);
			return;
		}
	}
	PushVector(self->Elements, m);
}

void bc_DeleteVTable(bc_VTable * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->Elements, VectorDeleterOfNull);
	MEM_FREE(self);
}
