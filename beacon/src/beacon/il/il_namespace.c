#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_NamespaceDeleteType(bc_VectorItem item);
static void il_NamespaceDeleteNamespace(bc_VectorItem item);

ILNamespace* NewILNamespace(bc_StringView namev) {
	ILNamespace* ret = (ILNamespace*)MEM_MALLOC(sizeof(ILNamespace));
	ret->Name = namev;
	ret->NamespaceList = bc_NewVector();
	ret->TypeList = bc_NewVector();
	ret->Parent = NULL;
	return ret;
}

ILNamespace* GetRootILNamespace(ILNamespace* self) {
	if(self == NULL) {
		return NULL;
	}
	if(self->Parent == NULL) {
		return self;
	}
	return GetRootILNamespace(self->Parent);
}

void DeleteILNamespace(ILNamespace* self) {
	if(self == NULL) {
		return;
	}
	bc_DeleteVector(self->NamespaceList, il_NamespaceDeleteNamespace);
	bc_DeleteVector(self->TypeList, il_NamespaceDeleteType);
	MEM_FREE(self);
}

//private
static void il_NamespaceDeleteType(bc_VectorItem item) {
	ILType* e = (ILType*)item;
	DeleteILType(e);
}

static void il_NamespaceDeleteNamespace(bc_VectorItem item) {
	ILNamespace* e = (ILNamespace*)item;
	DeleteILNamespace(e);
}