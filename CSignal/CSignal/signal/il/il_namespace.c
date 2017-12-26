#include "il_namespace.h"
#include "il_namespace_list.h"
#include "../util/text.h"
#include "il_class.h"
#include <stdlib.h>

//proto
static void il_namespace_class_delete(vector_item item);


il_namespace* il_namespace_new(const char* name) {
	il_namespace* ret = (il_namespace*)malloc(sizeof(il_namespace));
	ret->name = text_strdup(name);
	ret->namespace_list = il_namespace_list_new();
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

	il_namespace_list_dump(self->namespace_list, depth + 1);

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
	free(self->name);
	il_namespace_list_delete(self->namespace_list);
	vector_delete(self->class_list, il_namespace_class_delete);
	free(self);
}

//private
static void il_namespace_class_delete(vector_item item) {
	il_class* e = (il_class*)item;
	il_class_delete(e);
}