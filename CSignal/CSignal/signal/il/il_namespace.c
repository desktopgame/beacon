#include "il_namespace.h"
#include "../util/text.h"
#include "il_class.h"
#include <stdlib.h>
#include "../util/mem.h"

//proto
static void il_namespace_class_delete(vector_item item);
static void il_namespace_namespace_delete(vector_item item);

il_namespace* il_namespace_new(const char* name) {
	il_namespace* ret = (il_namespace*)MEM_MALLOC(sizeof(il_namespace));
	ret->name = text_strdup(name);
	ret->namespace_list = vector_new();
	ret->class_list = vector_new();
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

void il_namespace_dump(il_namespace* self, int depth) {
	text_putindent(depth);
	printf("namespace %s", self->name);
	text_putline();

	text_putindent(depth);
	printf("namespace list");
	text_putline();
	for (int i = 0; i < self->namespace_list->length; i++) {
		vector_item e = vector_at(self->namespace_list, i);
		il_namespace* iln = (il_namespace*)e;
		il_namespace_dump(iln, depth + 1);
	}

	text_putindent(depth);
	printf("class list");
	text_putline();
	for (int i = 0; i < self->class_list->length; i++) {
		vector_item e = vector_at(self->class_list, i);
		il_class* ilc = (il_class*)e;
		il_class_dump(ilc, depth + 1);
	}
	text_putline();
}

void il_namespace_delete(il_namespace* self) {
	if(self == NULL) {
		return;
	}
	MEM_FREE(self->name);
	vector_delete(self->namespace_list, il_namespace_namespace_delete);
	vector_delete(self->class_list, il_namespace_class_delete);
	MEM_FREE(self);
}

//private
static void il_namespace_class_delete(vector_item item) {
	il_class* e = (il_class*)item;
	il_class_delete(e);
}

static void il_namespace_namespace_delete(vector_item item) {
	il_namespace* e = (il_namespace*)item;
	il_namespace_delete(e);
}