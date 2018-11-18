#include "il_stmt_variable_decl_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../env/generic_type.h"
#include "../../env/namespace.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"

ILStatement * WrapILVariableDecl(ILVariableDecl * self) {
	ILStatement* ret = NewILStatement(ILSTMT_VARIABLE_DECL_T);
	ret->Kind.VariableDecl = self;
	return ret;
}

ILVariableDecl * NewILVariableDecl(StringView namev) {
	ILVariableDecl* ret = (ILVariableDecl*)MEM_MALLOC(sizeof(ILVariableDecl));
	ret->Name = namev;
	ret->GCache = NewGenericCache();
	return ret;
}

void GenerateILVariableDecl(ILVariableDecl * self, Enviroment * env, CallContext* cctx) {

}

void LoadILVariableDecl(ILVariableDecl * self, Enviroment* env, CallContext* cctx) {
	if(IsContainsSymbol(env->Symboles, self->Name)) {
		bc_Panic(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->Name)
		);
	}
	SymbolEntry* e = EntrySymbolTable(
		env->Symboles,
		ResolveImportManager(NULL, self->GCache, cctx),
		self->Name
	);
	if(e->GType->CoreType != NULL &&
	   e->GType->CoreType == TYPE_VOID) {
		   bc_Panic(BCERROR_VOID_DECL_T);
	}
}

void DeleteILVariableDecl(ILVariableDecl * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self);
}
