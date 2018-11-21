#include "vtable.h"
#include "../util/mem.h"
#include "method.h"
#include <assert.h>
#include "../il/call_context.h"

bc_VTable * bc_NewVTable() {
	bc_VTable* ret = (bc_VTable*)MEM_MALLOC(sizeof(bc_VTable));
	ret->Elements = bc_NewVector();
	ret->Parent = NULL;
	return ret;
}

void bc_CopyVTable(bc_VTable * src, bc_VTable * dst) {
	for (int i = 0; i < src->Elements->Length; i++) {
		bc_PushVector(dst->Elements, bc_AtVector(src->Elements, i));
	}
}

void bc_AddVTable(bc_VTable * self, bc_Method * m) {
	if (bc_IsStaticModifier(m->Modifier)) {
		return;
	}
	bc_PushVector(self->Elements, m);
}

void bc_ReplaceVTable(bc_VTable * self, bc_Method * m, bc_CallContext* cctx) {
	if (bc_IsStaticModifier(m->Modifier)) {
		return;
	}
	#if defined(DEBUG)
	const char* methodname = bc_Ref2Str(m->Name);
	#endif
	for (int i = 0; i < self->Elements->Length; i++) {
		bc_Method* e = (bc_Method*)bc_AtVector(self->Elements, i);
		//if (IsOverridedMethod(m, e, cctx)) {
		if (bc_IsOverridedMethod(e, m, cctx)) {
			bc_AssignVector(self->Elements, i, m);
			return;
		}
	}
	bc_PushVector(self->Elements, m);
}

void bc_DeleteVTable(bc_VTable * self) {
	if (self == NULL) {
		return;
	}
	bc_DeleteVector(self->Elements, bc_VectorDeleterOfNull);
	MEM_FREE(self);
}
