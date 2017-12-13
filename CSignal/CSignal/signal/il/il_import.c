#include "il_import.h"
#include "../util/text.h"
#include <stdlib.h>
#include <assert.h>

il_import* il_import_new(const char* path) {
	assert(path != NULL);
	il_import* ret = (il_import*)malloc(sizeof(il_import));
	ret->path = text_strdup(path);
	return ret;
}

void il_import_delete(il_import* self) {
	if(self == NULL) {
		return;
	}
	free(self->path);
	free(self);
}