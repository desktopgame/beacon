#include "il_factor_int_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"

il_factor * il_factor_wrap_int(il_factor_int * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_int;
	ret->u.int_ = self;
	return ret;
}

il_factor_int * il_factor_int_new(int32_t i) {
	il_factor_int* ret = (il_factor_int*)malloc(sizeof(il_factor_int));
	ret->value = i;
	return ret;
}

void il_factor_int_dump(il_factor_int * self, int depth) {
	text_putindent(depth);
	printf("Int %d", self->value);
	text_putline();
}

void il_factor_int_generate(il_factor_int * self, enviroment* env) {
}

void il_factor_int_delete(il_factor_int * self) {
	free(self);
}
