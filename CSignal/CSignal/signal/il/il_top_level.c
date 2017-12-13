#include "il_top_level.h"
#include <stdlib.h>

il_top_level* il_top_level_new() {
	il_top_level* ret = (il_top_level*)malloc(sizeof(il_top_level));
	ret->import_list = il_import_list_new();
	return ret;
}

void il_top_level_delete(il_top_level* self) {
	if(self == NULL) {
		return;
	}
	il_import_delete(self->import_list);
	free(self);
}