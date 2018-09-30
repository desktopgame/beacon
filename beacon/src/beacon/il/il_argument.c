#include "il_argument.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"
#include "../util/mem.h"

il_argument * NewILArgument() {
	void* block = MEM_MALLOC(sizeof(il_argument));
	assert(block != NULL);
	il_argument* ret = (il_argument*)block;
	ret->factor = NULL;
	return ret;
}

void DeleteILArgument(il_argument * self) {
	DeleteILFactor(self->factor);
	MEM_FREE(self);
}
