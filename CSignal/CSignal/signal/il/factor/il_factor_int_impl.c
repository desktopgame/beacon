#include "il_factor_int_impl.h"
#include <stdlib.h>

il_factor_int * il_factor_int_new(int32_t i) {
	il_factor_int* ret = (il_factor_int*)malloc(sizeof(il_factor_int));
	ret->value = i;
	return ret;
}

void il_factor_int_delete(il_factor_int * self) {
	free(self);
}
