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
	ret->Access = ACCESS_PUBLIC_T;
	ret->Parameters = NewVector();
	ret->Statements = NewVector();
	ret->Chain = NULL;
	return ret;
}

void DeleteILConstructor(ILConstructor * self) {
	DeleteILConstructorChain(self->Chain);
	DeleteVector(self->Parameters, ILConstructor_DeleteParameter);
	DeleteVector(self->Statements, ILConstructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void ILConstructor_DeleteParameter(VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void ILConstructor_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}