#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../il_type_argument.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/field.h"
#include "../../util/mem.h"
#include "../../vm/symbol_entry.h"
#include <assert.h>
#include <string.h>

//proto
static void ILVariable_check(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx);
static void ILVariable_check_instance(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx);
static void ILVariable_check_static(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx);
static void DeleteILFactor_typeargs(bc_VectorItem item);

bc_ILFactor * bc_WrapILVariable(bc_ILVariable * self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_VARIABLE_T);
	ret->Kind.Variable = self;
	return ret;
}

bc_ILVariable * bc_MallocILVariable(const char* filename, int lineno) {
	bc_ILVariable* ret = (bc_ILVariable*)bc_MXMalloc(sizeof(bc_ILVariable), filename, lineno);
	ret->FQCN = bc_MallocFQCNCache(filename, lineno);
	ret->TypeArgs = bc_MallocVector(filename, lineno);
	ret->Type = ILVARIABLE_TYPE_UNDEFINED_T;
	return ret;
}

void bc_GenerateILVariable(bc_ILVariable * self, bc_Enviroment* env, bc_CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		bc_GenerateILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		bc_GenerateILVariableStatic(self->Kind.Static, env, cctx);
	}
}

void bc_LoadILVariable(bc_ILVariable * self, bc_Enviroment * env, bc_CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		bc_LoadILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		bc_LoadILVariableStatic(self->Kind.Static, env, cctx);
	}
}

bc_GenericType* bc_EvalILVariable(bc_ILVariable * self, bc_Enviroment * env, bc_CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	bc_GenericType* ret = NULL;
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		ret = bc_EvalILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		ret = bc_EvalILVariableStatic(self->Kind.Static, env, cctx);
	}
	return ret;
}

char* bc_ILVariableToString(bc_ILVariable* self, bc_Enviroment* env) {
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		return bc_ILVariableLocalToString(self->Kind.Local, env);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		return bc_ILVariableStaticToString(self->Kind.Static, env);
	}
	return NULL;
}

void bc_DeleteILVariable(bc_ILVariable * self) {
	//MEM_FREE(self->name);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		bc_DeleteILVariableLocal(self->Kind.Local);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		bc_DeleteILVariableStatic(self->Kind.Static);
	}
	bc_DeleteFQCNCache(self->FQCN);
	bc_DeleteVector(self->TypeArgs, DeleteILFactor_typeargs);
	MEM_FREE(self);
}

//private
static void ILVariable_check(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx) {
	if(self->Type != ILVARIABLE_TYPE_UNDEFINED_T) {
		return;
	}
	assert(self->FQCN != NULL);
	//hoge, foo のような文字列の場合
	if(self->FQCN->Scope->Length == 0) {
		ILVariable_check_instance(self, env, cctx);
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->FQCN->Scope->Length > 0) {
		ILVariable_check_static(self, env, cctx);
	}
}

static void ILVariable_check_instance(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_Namespace* cur = bc_GetNamespaceCContext(cctx);
	bc_Class* ctype = bc_FindClassFromNamespace(cur, self->FQCN->Name);
	if(ctype == NULL) {
		ctype = bc_FindClassFromNamespace(bc_GetLangNamespace(), self->FQCN->Name);
	}
	//現在の名前空間から参照できるクラスがある場合
	if(ctype != NULL) {
		ILVariable_check_static(self, env, cctx);
	//ただのローカル変数の場合
	} else {
		bc_ILVariableLocal* lc = bc_NewILVariableLocal(self->FQCN->Name);
		self->Type = ILVARIABLE_TYPE_LOCAL_T;
		//値を入れ替え
		lc->TypeArgs = self->TypeArgs;
		self->TypeArgs = NULL;
		self->Kind.Local = lc;
	}
}

static void ILVariable_check_static(bc_ILVariable* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_ILVariableStatic* st = bc_NewILVariableStatic();
	self->Type = ILVARIABLE_TYPE_STATIC_T;
	//値を入れ替え
	st->FQCN = self->FQCN;
	st->TypeArgs = self->TypeArgs;
	self->FQCN = NULL;
	self->TypeArgs = NULL;
	self->Kind.Static = st;
}

static void DeleteILFactor_typeargs(bc_VectorItem item) {
	bc_ILTypeArgument* e = (bc_ILTypeArgument*)item;
	bc_DeleteILTypeArgument(e);
}