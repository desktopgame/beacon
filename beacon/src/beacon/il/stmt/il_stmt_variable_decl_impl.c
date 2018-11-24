#include "il_stmt_variable_decl_impl.h"
#include "../../env/class_loader.h"
#include "../../env/generic_type.h"
#include "../../env/import_manager.h"
#include "../../env/namespace.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"

bc_ILStatement* bc_WrapILVariableDecl(bc_ILVariableDecl* self) {
        bc_ILStatement* ret = bc_NewILStatement(ILSTMT_VARIABLE_DECL_T);
        ret->Kind.VariableDecl = self;
        return ret;
}

bc_ILVariableDecl* bc_NewILVariableDecl(bc_StringView namev) {
        bc_ILVariableDecl* ret =
            (bc_ILVariableDecl*)MEM_MALLOC(sizeof(bc_ILVariableDecl));
        ret->Name = namev;
        ret->GCache = bc_NewGenericCache();
        return ret;
}

void bc_GenerateILVariableDecl(bc_ILVariableDecl* self, bc_Enviroment* env,
                               bc_CallContext* cctx) {}

void bc_LoadILVariableDecl(bc_ILVariableDecl* self, bc_Enviroment* env,
                           bc_CallContext* cctx) {
        if (bc_IsContainsSymbol(env->Symboles, self->Name)) {
                bc_Panic(BCERROR_OVERWRAP_VARIABLE_NAME_T,
                         bc_Ref2Str(self->Name));
        }
        bc_SymbolEntry* e = bc_EntrySymbolTable(
            env->Symboles, bc_ResolveImportManager(NULL, self->GCache, cctx),
            self->Name);
        if (e->GType->CoreType != NULL && e->GType->CoreType == BC_TYPE_VOID) {
                bc_Panic(BCERROR_VOID_DECL_T);
        }
}

void bc_DeleteILVariableDecl(bc_ILVariableDecl* self) {
        if (self == NULL) {
                return;
        }
        MEM_FREE(self);
}
