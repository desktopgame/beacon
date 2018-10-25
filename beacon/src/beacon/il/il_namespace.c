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
	ret->namev = namev;
	ret->Namespacelist = NewVector();
	ret->type_list = NewVector();
	ret->parent = NULL;
	return ret;
}

ILNamespace* GetRootILNamespace(ILNamespace* self) {
	if(self == NULL) {
		return NULL;
	}
	if(self->parent == NULL) {
		return self;
	}
	return GetRootILNamespace(self->parent);
}

void DeleteILNamespace(ILNamespace* self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->Namespacelist, il_NamespaceDeleteNamespace);
	DeleteVector(self->type_list, il_NamespaceDeleteType);
	MEM_FREE(self);
}

//private
static void il_NamespaceDeleteType(VectorItem item) {
	il_type* e = (il_type*)item;
	DeleteILType(e);
}

static void il_NamespaceDeleteNamespace(VectorItem item) {
	ILNamespace* e = (ILNamespace*)item;
	DeleteILNamespace(e);
}