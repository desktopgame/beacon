#include "il_constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

//proto
static void ILConstructor_DeleteParameter(bc_VectorItem item);
static void ILConstructor_stmt_delete(bc_VectorItem item);

ILConstructor * NewILConstructor() {
	ILConstructor* ret = (ILConstructor*)MEM_MALLOC(sizeof(ILConstructor));
	ret->Access = ACCESS_PUBLIC_T;
	ret->Parameters = bc_NewVector();
	ret->Statements = bc_NewVector();
	ret->Chain = NULL;
	return ret;
}

void DeleteILConstructor(ILConstructor * self) {
	DeleteILConstructorChain(self->Chain);
	bc_DeleteVector(self->Parameters, ILConstructor_DeleteParameter);
	bc_DeleteVector(self->Statements, ILConstructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void ILConstructor_DeleteParameter(bc_VectorItem item) {
	ILParameter* e = (ILParameter*)item;
	DeleteILParameter(e);
}

static void ILConstructor_stmt_delete(bc_VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}