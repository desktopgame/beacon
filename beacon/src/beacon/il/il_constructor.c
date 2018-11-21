#include "il_constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include "il_constructor_chain.h"

//proto
static void ILConstructor_DeleteParameter(bc_VectorItem item);
static void ILConstructor_stmt_delete(bc_VectorItem item);

bc_ILConstructor * bc_NewILConstructor() {
	bc_ILConstructor* ret = (bc_ILConstructor*)MEM_MALLOC(sizeof(bc_ILConstructor));
	ret->Access = ACCESS_PUBLIC_T;
	ret->Parameters = bc_NewVector();
	ret->Statements = bc_NewVector();
	ret->Chain = NULL;
	return ret;
}

void bc_DeleteILConstructor(bc_ILConstructor * self) {
	bc_DeleteILConstructorChain(self->Chain);
	bc_DeleteVector(self->Parameters, ILConstructor_DeleteParameter);
	bc_DeleteVector(self->Statements, ILConstructor_stmt_delete);
	MEM_FREE(self);
}
//private
static void ILConstructor_DeleteParameter(bc_VectorItem item) {
	bc_ILParameter* e = (bc_ILParameter*)item;
	bc_DeleteILParameter(e);
}

static void ILConstructor_stmt_delete(bc_VectorItem item) {
	bc_ILStatement* e = (bc_ILStatement*)item;
	bc_DeleteILStmt(e);
}