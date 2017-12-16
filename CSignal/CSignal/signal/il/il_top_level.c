#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>

il_top_level* il_top_level_new() {
	il_top_level* ret = (il_top_level*)malloc(sizeof(il_top_level));
	ret->import_list = il_import_list_new();
	ret->namespace_list = il_namespace_list_new();
	return ret;
}

void il_top_level_dump(il_top_level* self, int depth) {
	printf("top_level");
	text_putline();
	il_import_list_dump(self->import_list, depth + 1);
	il_namespace_list_dump(self->namespace_list, depth + 1);
}

void il_top_level_delete(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	il_import_list_delete(self->import_list);
	il_namespace_list_delete(self->namespace_list);
	free(self);
}