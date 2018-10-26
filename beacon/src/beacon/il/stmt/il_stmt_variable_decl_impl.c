#include "il_stmt_variable_decl_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"

il_stmt * WrapILVariableDecl(il_stmt_variable_decl * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_VARIABLE_DECL_T);
	ret->u.variable_decl = self;
	return ret;
}

il_stmt_variable_decl * NewILVariableDecl(StringView namev) {
	il_stmt_variable_decl* ret = (il_stmt_variable_decl*)MEM_MALLOC(sizeof(il_stmt_variable_decl));
	ret->namev = namev;
	ret->fqcn = NewGenericCache();
	return ret;
}

void GenerateILVariableDecl(il_stmt_variable_decl * self, Enviroment * env, CallContext* cctx) {

}

void LoadILVariableDecl(il_stmt_variable_decl * self, Enviroment* env, CallContext* cctx) {
	if(IsContainsSymbol(env->Symboles, self->namev)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	SymbolEntry* e = EntrySymbolTable(
		env->Symboles,
		ResolveImportManager(NULL, self->fqcn, cctx),
		self->namev
	);
	if(e->GType->CoreType != NULL &&
	   e->GType->CoreType == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_DECL_T);
	}
}

void DeleteILVariableDecl(il_stmt_variable_decl * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self);
}
