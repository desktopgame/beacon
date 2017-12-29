#include "il_type.h"
#include "../util/text.h"
#include <stdlib.h>
#include "../util/mem.h"

il_type* il_type_new(const char* name) {
	il_type* ret = (il_type*)MEM_MALLOC(sizeof(il_type));
	ret->name = text_strdup(name);
	return ret;
}

void il_type_delete(il_type* self) {
	if(self == NULL) {
		return;
	}
	MEM_FREE(self->name);
	MEM_FREE(self);
}