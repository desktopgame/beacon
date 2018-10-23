#include "il_property_body.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"
#include "il_stmt_interface.h"

static void ILPropertyBody_stmt_delete(VectorItem item);

ILPropertyBody* MallocILPropertyBody(ILPropertyBodyTag tag, const char* filename, int lineno) {
	ILPropertyBody* ret = mem_malloc(sizeof(ILPropertyBody), filename, lineno);
	ret->Statements = NewVector();
	ret->Tag = tag;
	ret->IsShort = false;
	return ret;
}

void DeleteILPropertyBody(ILPropertyBody* self) {
	DeleteVector(self->Statements, ILPropertyBody_stmt_delete);
	MEM_FREE(self);
}
//private
static void ILPropertyBody_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}