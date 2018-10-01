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

il_stmt_variable_decl * NewILVariableDecl(string_view namev) {
	il_stmt_variable_decl* ret = (il_stmt_variable_decl*)MEM_MALLOC(sizeof(il_stmt_variable_decl));
	ret->namev = namev;
	ret->fqcn = generic_cache_new();
	return ret;
}

void GenerateILVariableDecl(il_stmt_variable_decl * self, enviroment * env, call_context* cctx) {

}

void LoadILVariableDecl(il_stmt_variable_decl * self, struct enviroment* env, call_context* cctx) {
	if(IsContainsSymbol(env->sym_table, self->namev)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	symbol_entry* e = EntrySymbolTable(
		env->sym_table,
		import_manager_resolve(NULL, self->fqcn, cctx),
		self->namev
	);
	if(e->gtype->core_type != NULL &&
	   e->gtype->core_type == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_DECL_T);
	}
}

void DeleteILVariableDecl(il_stmt_variable_decl * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self);
}
