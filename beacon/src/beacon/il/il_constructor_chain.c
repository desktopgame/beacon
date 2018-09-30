#include "il_constructor_chain.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_argument.h"
#include <stdio.h>

//proto
static void il_constructor_argument_delete(VectorItem item);

il_constructor_chain * il_constructor_chain_new() {
	il_constructor_chain* ret = (il_constructor_chain*)MEM_MALLOC(sizeof(il_constructor_chain));
	ret->type = CHAIN_TYPE_THIS_T;
	ret->argument_list = NewVector();
	ret->c = NULL;
	ret->constructor_index = -1;
	return ret;
}

void il_constructor_chain_delete(il_constructor_chain * self) {
	if (self == NULL) {
		return;
	}
	DeleteVector(self->argument_list, il_constructor_argument_delete);
	MEM_FREE(self);
}
//private
static void il_constructor_argument_delete(VectorItem item) {
	il_argument* e = (il_argument*)item;
	DeleteILArgument(e);
}