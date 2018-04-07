#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

parameter * parameter_new(const char * name) {
	parameter* ret = (parameter*)MEM_MALLOC(sizeof(parameter));
	ret->name = text_strdup(name);
	return ret;
}

void parameter_delete(parameter * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}
