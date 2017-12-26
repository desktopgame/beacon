#include "il_argument.h"
#include <stdio.h>
#include <stdlib.h>
//#include <stdio.h>
#include <assert.h>
#include "../util/text.h"

il_argument * il_argument_new() {
	void* block = malloc(sizeof(il_argument));
	assert(block != NULL);
	il_argument* ret = (il_argument*)block;
	//ret->name = text_strdup(name);
	ret->factor = NULL;
	return ret;
}

void il_argument_dump(il_argument * self, int depth) {
	text_putindent(depth);
	printf("argument");
	text_putline();
	il_factor_dump(self->factor, depth + 1);
}

void il_argument_delete(il_argument * self) {
	il_factor_delete(self->factor);
	free(self);
}
