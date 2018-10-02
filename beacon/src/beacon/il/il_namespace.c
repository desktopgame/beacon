#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_namespace_DeleteType(VectorItem item);
static void il_namespace_DeleteNamespace(VectorItem item);

il_namespace* NewILNamespace(string_view namev) {
	il_namespace* ret = (il_namespace*)MEM_MALLOC(sizeof(il_namespace));
	ret->namev = namev;
	ret->namespace_list = NewVector();
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
	DeleteVector(self->namespace_list, il_namespace_DeleteNamespace);
	DeleteVector(self->type_list, il_namespace_DeleteType);
	MEM_FREE(self);
}

//private
static void il_namespace_DeleteType(VectorItem item) {
	il_type* e = (il_type*)item;
	DeleteILType(e);
}

static void il_namespace_DeleteNamespace(VectorItem item) {
	il_namespace* e = (il_namespace*)item;
	DeleteILNamespace(e);
}