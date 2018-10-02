#include "il_stmt_variable_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <assert.h>

il_stmt * WrapILVariableInit(il_stmt_variable_init * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->type = ILSTMT_VARIABLE_INIT_T;
	ret->u.variable_init = self;
	return ret;
}

il_stmt_variable_init * NewILVariableInit(string_view namev) {
	il_stmt_variable_init* ret = (il_stmt_variable_init*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->namev = namev;
	ret->fact = NULL;
	ret->fqcn = NewGenericCache();
	return ret;
}

void GenerateILVariableInit(il_stmt_variable_init * self, enviroment * env, call_context* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	//宣言型と代入型が異なる場合
	generic_type* ga = EvalILFactor(self->fact, env, cctx);
	generic_type* gb = ResolveImportManager(NULL, self->fqcn, cctx);
	//voidは代入できない
	assert(gb != NULL);
	BC_ERROR();
	if((ga->core_type != NULL && ga->core_type == TYPE_VOID) ||
	   (gb->core_type != NULL && gb->core_type == TYPE_VOID)) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
	int dist = DistanceGenericType(gb, ga, cctx);
	if (dist < 0) {
		ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
			Ref2Str(self->namev)
		);
	}
	AddOpcodeBuf(env->buf, OP_STORE);
	AddOpcodeBuf(env->buf, self->sym->index);
}

void LoadILVariableInit(il_stmt_variable_init * self, enviroment * env, call_context* cctx) {
	LoadILFactor(self->fact, env, cctx);
	if(IsContainsSymbol(env->sym_table, self->namev)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	generic_type* gt = ResolveImportManager(NULL, self->fqcn, cctx);
	if(gt == NULL) {
		ThrowBCError(
			BCERROR_UNDEFINED_TYPE_DECL_T,
			Ref2Str(self->fqcn->fqcn->namev)
		);
		return;
	}
	symbol_entry* e = EntrySymbolTable(
		env->sym_table,
		gt,
		self->namev
	);
	self->sym = e;
	assert(e->gtype != NULL);
}

void DeleteILVariableInit(il_stmt_variable_init * self) {
	DeleteILFactor(self->fact);
	DeleteGenericCache(self->fqcn);
	MEM_FREE(self);
}
