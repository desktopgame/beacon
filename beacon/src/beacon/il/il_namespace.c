#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_NamespaceDeleteType(VectorItem item);
static void il_NamespaceDeleteNamespace(VectorItem item);

ILNamespace* NewILNamespace(StringView namev) {
	ILNamespace* ret = (ILNamespace*)MEM_MALLOC(sizeof(ILNamespace));
	ret->Name = namev;
	ret->NamespaceList = NewVector();
	ret->TypeList = NewVector();
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
	DeleteVector(self->NamespaceList, il_NamespaceDeleteNamespace);
	DeleteVector(self->TypeList, il_NamespaceDeleteType);
	MEM_FREE(self);
}

//private
static void il_NamespaceDeleteType(VectorItem item) {
	ILType* e = (ILType*)item;
	DeleteILType(e);
}

static void il_NamespaceDeleteNamespace(VectorItem item) {
	ILNamespace* e = (ILNamespace*)item;
	DeleteILNamespace(e);
}