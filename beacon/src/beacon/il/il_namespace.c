#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_NamespaceDeleteType(VectorItem item);
static void il_NamespaceDeleteNamespace(VectorItem item);

il_namespace* NewILNamespace(StringView namev) {
	il_namespace* ret = (il_namespace*)MEM_MALLOC(sizeof(il_namespace));
	ret->namev = namev;
	ret->Namespacelist = NewVector();
	ret->type_list = NewVector();
	ret->parent = NULL;
	return ret;
}

il_namespace* GetRootILNamespace(il_namespace* self) {
	if(self == NULL) {
		return NULL;
	}
	if(self->parent == NULL) {
		return self;
	}
	return GetRootILNamespace(self->parent);
}

void DeleteILNamespace(il_namespace* self) {
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
	il_namespace* e = (il_namespace*)item;
	DeleteILNamespace(e);
}