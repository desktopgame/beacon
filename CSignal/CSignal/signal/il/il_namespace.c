#include "il_namespace.h"
#include "il_namespace_list.h"
#include "../util/text.h"
#include <stdlib.h>

il_namespace* il_namespace_new(const char* name) {
	il_namespace* ret = (il_namespace*)malloc(sizeof(il_namespace));
	ret->name = text_strdup(name);
	ret->namespace_list = il_namespace_list_new();
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
	text_putline();
}

void il_namespace_delete(il_namespace* self) {
	if(self == NULL) {
		return;
	}
	free(self->name);
	il_namespace_list_delete(self->namespace_list);
	free(self);
}