#include "il_factor_char_impl.h"
#include <stdlib.h>

il_factor_char * il_factor_char_new(char c) {
	il_factor_char* ret = (il_factor_char*)malloc(sizeof(il_factor_char));
	ret->value = c;
	return ret;
}

void il_factor_char_delete(il_factor_char * self) {
	free(self);
}
