#include "il_factor_double_impl.h"
#include <stdlib.h>

il_factor_double * il_factor_double_new(double d) {
	il_factor_double* ret = (il_factor_double*)malloc(sizeof(il_factor_double));
	ret->value = d;
	return ret;
}

void il_factor_double_delete(il_factor_double * self) {
	free(self);
}
