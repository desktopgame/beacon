#include "il_constructor_chain.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_argument.h"
#include <stdio.h>

//proto
static void il_constructor_argument_delete(VectorItem item);

ILConstructorChain * NewILConstructorChain() {
	ILConstructorChain* ret = (ILConstructorChain*)MEM_MALLOC(sizeof(ILConstructorChain));
	ret->type = CHAIN_TYPE_THIS_T;
	ret->argument_list = NewVector();
	ret->c = NULL;
	ret->constructor_index = -1;
	return ret;
}

void DeleteILConstructorChain(ILConstructorChain * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->argument_list, il_constructor_argument_delete);
	MEM_FREE(self);
}
//private
static void il_constructor_argument_delete(VectorItem item) {
	ILArgument* e = (ILArgument*)item;
	DeleteILArgument(e);
}