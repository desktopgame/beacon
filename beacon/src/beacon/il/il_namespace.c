#include "il_namespace.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "il_type_interface.h"

//proto
static void il_namespace_type_delete(vector_item item);
static void il_namespace_namespace_delete(vector_item item);

il_namespace* il_namespace_new(string_view namev) {
	il_namespace* ret = (il_namespace*)MEM_MALLOC(sizeof(il_namespace));
	ret->namev = namev;
	ret->namespace_list = vector_new();
	ret->type_list = vector_new();
	ret->parent = NULL;
	return ret;
}

il_namespace* il_namespace_root(il_namespace* self) {
	if(self == NULL) {
		return NULL;
	}
	if(self->parent == NULL) {
		return self;
	}
	return il_namespace_root(self->parent);
}

void il_namespace_delete(il_namespace* self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->namespace_list, il_namespace_namespace_delete);
	vector_delete(self->type_list, il_namespace_type_delete);
	MEM_FREE(self);
}

//private
static void il_namespace_type_delete(vector_item item) {
	il_type* e = (il_type*)item;
	il_type_delete(e);
}

static void il_namespace_namespace_delete(vector_item item) {
	il_namespace* e = (il_namespace*)item;
	il_namespace_delete(e);
}