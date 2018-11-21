#include "il_argument.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"
#include "../util/mem.h"

bc_ILArgument * bc_NewILArgument() {
	void* block = MEM_MALLOC(sizeof(bc_ILArgument));
	assert(block != NULL);
	bc_ILArgument* ret = (bc_ILArgument*)block;
	ret->Factor = NULL;
	return ret;
}

void bc_DeleteILArgument(bc_ILArgument * self) {
	bc_DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
