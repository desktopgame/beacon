#include "il_constructor.h"
#include "../util/mem.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

il_constructor * il_constructor_new() {
	il_constructor* ret = (il_constructor*)MEM_MALLOC(sizeof(il_constructor));
	ret->access = access_public;
	ret->parameter_list = vector_new();
	ret->statement_list = vector_new();
	ret->chain = NULL;
	return ret;
}

void il_constructor_dump(il_constructor * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
//	printf(" ");
//	modifier_print(self->modifier);
	printf(" constructor");
//	fqcn_cache_print(self->return_fqcn);
	text_putline();
	if (self->chain != NULL) {
		il_constructor_chain_dump(self->chain, depth + 1);
	}
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		il_parameter* p = (il_parameter*)e;
		il_parameter_dump(p, depth + 1);
	}
	for (int i = 0; i < self->statement_list->length; i++) {
		vector_item e = vector_at(self->statement_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
}

void il_constructor_delete(il_constructor * self) {
}
