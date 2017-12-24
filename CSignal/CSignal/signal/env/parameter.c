#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"

parameter * parameter_new(const char * name) {
	parameter* ret = (parameter*)malloc(sizeof(parameter));
	ret->name = text_strdup(name);
	ret->classz = NULL;
	return ret;
}

void parameter_delete(parameter * self) {
	free(self->name);
	free(self);
}
