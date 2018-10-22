#include "il_argument.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"
#include "../util/mem.h"

ILArgument * NewILArgument() {
	void* block = MEM_MALLOC(sizeof(ILArgument));
	assert(block != NULL);
	ILArgument* ret = (ILArgument*)block;
	ret->Factor = NULL;
	return ret;
}

void DeleteILArgument(ILArgument * self) {
	DeleteILFactor(self->Factor);
	MEM_FREE(self);
}
