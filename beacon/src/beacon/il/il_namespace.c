#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_NamespaceDeleteType(bc_VectorItem item);
static void il_NamespaceDeleteNamespace(bc_VectorItem item);

bc_ILNamespace* bc_NewILNamespace(bc_StringView namev) {
	bc_ILNamespace* ret = (bc_ILNamespace*)MEM_MALLOC(sizeof(bc_ILNamespace));
	ret->Name = namev;
	ret->NamespaceList = bc_NewVector();
	ret->TypeList = bc_NewVector();
	ret->Parent = NULL;
	return ret;
}

bc_ILNamespace* bc_GetRootILNamespace(bc_ILNamespace* self) {
	if(self == NULL) {
		return NULL;
	}
	if(self->Parent == NULL) {
		return self;
	}
	return bc_GetRootILNamespace(self->Parent);
}

void bc_DeleteILNamespace(bc_ILNamespace* self) {
	if(self == NULL) {
		return;
	}
	bc_DeleteVector(self->NamespaceList, il_NamespaceDeleteNamespace);
	bc_DeleteVector(self->TypeList, il_NamespaceDeleteType);
	MEM_FREE(self);
}

//private
static void il_NamespaceDeleteType(bc_VectorItem item) {
	bc_ILType* e = (bc_ILType*)item;
	bc_DeleteILType(e);
}

static void il_NamespaceDeleteNamespace(bc_VectorItem item) {
	bc_ILNamespace* e = (bc_ILNamespace*)item;
	bc_DeleteILNamespace(e);
}