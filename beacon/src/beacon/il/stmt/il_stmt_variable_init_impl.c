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

ILStatement * WrapILVariableInit(ILVariableInit * self) {
	ILStatement* ret = (ILStatement*)MEM_MALLOC(sizeof(ILVariableInit));
	ret->type = ILSTMT_VARIABLE_INIT_T;
	ret->u.variable_init = self;
	return ret;
}

ILVariableInit * NewILVariableInit(StringView namev) {
	ILVariableInit* ret = (ILVariableInit*)MEM_MALLOC(sizeof(ILVariableInit));
	ret->Name = namev;
	ret->Value = NULL;
	ret->GCache = NewGenericCache();
	return ret;
}

void GenerateILVariableInit(ILVariableInit * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->Value, env, cctx);
	//宣言型と代入型が異なる場合
	GenericType* ga = EvalILFactor(self->Value, env, cctx);
	GenericType* gb = ResolveImportManager(NULL, self->GCache, cctx);
	//voidは代入できない
	assert(gb != NULL);
	BC_ERROR();
	if((ga->CoreType != NULL && ga->CoreType == TYPE_VOID) ||
	   (gb->CoreType != NULL && gb->CoreType == TYPE_VOID)) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
	int dist = DistanceGenericType(gb, ga, cctx);
	if (dist < 0) {
		ThrowBCError(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
			Ref2Str(self->Name)
		);
	}
	AddOpcodeBuf(env->Bytecode, OP_STORE);
	AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void LoadILVariableInit(ILVariableInit * self, Enviroment * env, CallContext* cctx) {
	LoadILFactor(self->Value, env, cctx);
	if(IsContainsSymbol(env->Symboles, self->Name)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->Name)
		);
	}
	GenericType* gt = ResolveImportManager(NULL, self->GCache, cctx);
	if(gt == NULL) {
		ThrowBCError(
			BCERROR_UNDEFINED_TYPE_DECL_T,
			Ref2Str(self->GCache->FQCN->Name)
		);
		return;
	}
	SymbolEntry* e = EntrySymbolTable(
		env->Symboles,
		gt,
		self->Name
	);
	self->Symbol = e;
	assert(e->GType != NULL);
}

void DeleteILVariableInit(ILVariableInit * self) {
	DeleteILFactor(self->Value);
	DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
