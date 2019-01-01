#include "il_property_body.h"
#include "../env/generic_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_stmt_interface.h"

static void ILPropertyBody_stmt_delete(bc_VectorItem item);

bc_ILPropertyBody* bc_MallocILPropertyBody(bc_ILPropertyBodyTag tag,
                                           const char* filename, int lineno) {
        bc_ILPropertyBody* ret =
            bc_MXMalloc(sizeof(bc_ILPropertyBody), filename, lineno);
        ret->Statements = bc_NewVector();
        ret->Tag = tag;
        ret->IsShort = false;
        return ret;
}

void bc_DeleteILPropertyBody(bc_ILPropertyBody* self) {
        bc_DeleteVector(self->Statements, ILPropertyBody_stmt_delete);
        MEM_FREE(self);
}
// private
static void ILPropertyBody_stmt_delete(bc_VectorItem item) {
        bc_ILStatement* e = (bc_ILStatement*)item;
        bc_DeleteILStmt(e);
}