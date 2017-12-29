#include "il_import.h"
#include "../util/text.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"

il_import* il_import_new(const char* path) {
	assert(path != NULL);
	il_import* ret = (il_import*)MEM_MALLOC(sizeof(il_import));
	ret->path = text_strdup(path);
	return ret;
}

void il_import_dump(il_import* self, int depth) {
	text_putindent(depth);
	printf("import %s", self->path);
	text_putline();
}

void il_import_delete(il_import* self) {
	if(self == NULL) {
		return;
	}
	MEM_FREE(self->path);
	MEM_FREE(self);
}