#include "il_constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

//proto
static void ILConstructor_DeleteParameter(VectorItem item);
static void ILConstructor_stmt_delete(VectorItem item);

ILConstructor * NewILConstructor() {
	ILConstructor* ret = (ILConstructor*)MEM_MALLOC(sizeof(ILConstructor));
	ret->access = ACCESS_PUBLIC_T;
	ret->parameter_list = NewVector();
	ret->statement_list = NewVector();
	ret->chain = NULL;
	return ret;
}

void DeleteILConstructor(ILConstructor * self) {
	DeleteILConstructorChain(self->chain);
	DeleteVector(self->parameter_list, ILConstructor_DeleteParameter);
	DeleteVector(self->statement_list, ILConstructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void ILConstructor_DeleteParameter(VectorItem item) {
	il_parameter* e = (il_parameter*)item;
	DeleteILParameter(e);
}

static void ILConstructor_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}