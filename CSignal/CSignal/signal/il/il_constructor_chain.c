#include "il_constructor_chain.h"
#include "../util/mem.h"

il_constructor_chain * il_constructor_chain_new() {
	il_constructor_chain* ret = (il_constructor_chain*)MEM_MALLOC(sizeof(il_constructor_chain));
	ret->type = ilchain_this;
	ret->argument_list = vector_new();
	return ret;
}

void il_constructor_chain_delete(il_constructor_chain * self) {
	MEM_FREE(self);
}
