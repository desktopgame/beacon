#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "../util/mem.h"

il_parameter * il_parameter_new(const char * name) {
	il_parameter* ret = (il_parameter*)MEM_MALLOC(sizeof(il_parameter));
	ret->name = text_strdup(name);
	ret->param_type = il_param_type_default;
	ret->fqcn = fqcn_cache_new();
	return ret;
}

void il_parameter_dump(il_parameter * self, int depth) {
	text_putindent(depth);
	printf("parameter ");
	fqcn_cache_print(self->fqcn);
	text_putline();
}

void il_parameter_delete(il_parameter * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self->name);
//	il_type_delete(self->type);
	MEM_FREE(self);
}
