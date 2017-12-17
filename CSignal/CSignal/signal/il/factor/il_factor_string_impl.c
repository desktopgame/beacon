#include "il_factor_string_impl.h"
#include <stdlib.h>
#include "../../util/text.h"

il_factor_string * il_factor_string_new(const char * name) {
	il_factor_string* ret = (il_factor_string*)malloc(sizeof(il_factor_string));
	ret->value = text_strdup(name);
	return ret;
}

void il_factor_string_delete(il_factor_string * self) {
	free(self->value);
	free(self);
}
