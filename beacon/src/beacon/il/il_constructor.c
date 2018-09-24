#include "il_constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

//proto
static void il_constructor_parameter_delete(vector_item item);
static void il_constructor_stmt_delete(vector_item item);

il_constructor * il_constructor_new() {
	il_constructor* ret = (il_constructor*)MEM_MALLOC(sizeof(il_constructor));
	ret->access = access_public_T;
	ret->parameter_list = vector_new();
	ret->statement_list = vector_new();
	ret->chain = NULL;
	return ret;
}

void il_constructor_delete(il_constructor * self) {
	il_constructor_chain_delete(self->chain);
	vector_delete(self->parameter_list, il_constructor_parameter_delete);
	vector_delete(self->statement_list, il_constructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void il_constructor_parameter_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_constructor_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}