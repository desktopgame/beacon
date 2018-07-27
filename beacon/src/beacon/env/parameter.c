#include "parameter.h"
#include <stdlib.h>
#include "../util/text.h"
#include "../util/mem.h"
#include "../env/generic_type.h"

parameter * parameter_new(string_view namev) {
	parameter* ret = (parameter*)MEM_MALLOC(sizeof(parameter));
	ret->namev = namev;
	ret->gtype = NULL;
	return ret;
}

void parameter_delete(parameter * self) {
	MEM_FREE(self);
}
