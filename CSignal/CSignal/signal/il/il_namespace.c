#include "il_namespace.h"
#include "il_namespace_list.h"
#include "../util/text.h"
#include <stdlib.h>

il_namespace* il_namespace_new(const char* name) {
	il_namespace* ret = (il_namespace*)malloc(sizeof(il_namespace));
	ret->name = text_strdup(name);
	ret->namespace_list = NULL;
	return ret;
}

void il_namespace_delete(il_namespace* self) {
	if(self == NULL) {
		return;
	}
	free(self->name);
	il_namespace_list_delete(self->namespace_list);
	free(self);
}