#include "il_type.h"
#include "../util/text.h"
#include <stdlib.h>

il_type* il_type_new(const char* name) {
	il_type* ret = (il_type*)malloc(sizeof(il_type));
	ret->name = text_strdup(name);
	return ret;
}

void il_type_delete(il_type* self) {
	if(self == NULL) {
		return;
	}
	free(self->name);
	free(self);
}