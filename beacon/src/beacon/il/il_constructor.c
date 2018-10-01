#include "il_constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

//proto
static void il_constructor_DeleteParameter(VectorItem item);
static void il_constructor_stmt_delete(VectorItem item);

il_constructor * NewILConstructor() {
	il_constructor* ret = (il_constructor*)MEM_MALLOC(sizeof(il_constructor));
	ret->access = ACCESS_PUBLIC_T;
	ret->parameter_list = NewVector();
	ret->statement_list = NewVector();
	ret->chain = NULL;
	return ret;
}

void DeleteILConstructor(il_constructor * self) {
	DeleteILConstructorChain(self->chain);
	DeleteVector(self->parameter_list, il_constructor_DeleteParameter);
	DeleteVector(self->statement_list, il_constructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void il_constructor_DeleteParameter(VectorItem item) {
	il_parameter* e = (il_parameter*)item;
	DeleteILParameter(e);
}

static void il_constructor_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}