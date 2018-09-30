#include "il_property_body.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"
#include "il_stmt_interface.h"

static void il_property_body_stmt_delete(VectorItem item);

il_property_body* MallocILPropertyBody(il_property_body_tag tag, const char* filename, int lineno) {
	il_property_body* ret = mem_malloc(sizeof(il_property_body), filename, lineno);
	ret->statement_list = NewVector();
	ret->tag = tag;
	ret->is_short = false;
	return ret;
}

void DeleteILPropertyBody(il_property_body* self) {
	DeleteVector(self->statement_list, il_property_body_stmt_delete);
	MEM_FREE(self);
}
//private
static void il_property_body_stmt_delete(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	DeleteILStmt(e);
}