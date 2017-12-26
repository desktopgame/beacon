#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>
#include "il_import.h"

//proto
static void il_top_level_import_delete(vector_item item);

il_top_level* il_top_level_new() {
	il_top_level* ret = (il_top_level*)malloc(sizeof(il_top_level));
	ret->import_list = vector_new();
	ret->namespace_list = il_namespace_list_new();
	return ret;
}

void il_top_level_dump(il_top_level* self, int depth) {
	printf("top_level");
	text_putline();
	for (int i = 0; i < self->import_list->length; i++) {
		vector_item e = vector_at(self->import_list, i);
		il_import* ili = (il_import*)e;
		il_import_dump(ili, depth + 1);
	}
	il_namespace_list_dump(self->namespace_list, depth + 1);
}

void il_top_level_delete(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	vector_delete(self->import_list, il_top_level_import_delete);
	il_namespace_list_delete(self->namespace_list);
	free(self);
}

//private
static void il_top_level_import_delete(vector_item item) {
	il_import* e = (il_import*)item;
	il_import_delete(e);
}