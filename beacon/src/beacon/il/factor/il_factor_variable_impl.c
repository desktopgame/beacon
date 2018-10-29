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
static void ILVariable_check(ILVariable* self, Enviroment* env, CallContext* cctx);
static void ILVariable_check_instance(ILVariable* self, Enviroment* env, CallContext* cctx);
static void ILVariable_check_static(ILVariable* self, Enviroment* env, CallContext* cctx);
static void DeleteILFactor_typeargs(VectorItem item);

ILFactor * WrapILVariable(ILVariable * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_VARIABLE_T);
	ret->u.variable_ = self;
	return ret;
}

ILVariable * MallocILVariable(const char* filename, int lineno) {
	ILVariable* ret = (ILVariable*)mem_malloc(sizeof(ILVariable), filename, lineno);
	ret->FQCN = MallocFQCNCache(filename, lineno);
	ret->TypeArgs = MallocVector(filename, lineno);
	ret->Type = ILVARIABLE_TYPE_UNDEFINED_T;
	return ret;
}

void GenerateILVariable(ILVariable * self, Enviroment* env, CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		GenerateILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		GenerateILVariableStatic(self->Kind.Static, env, cctx);
	}
}

void LoadILVariable(ILVariable * self, Enviroment * env, CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		LoadILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		LoadILVariableStatic(self->Kind.Static, env, cctx);
	}
}

GenericType* EvalILVariable(ILVariable * self, Enviroment * env, CallContext* cctx) {
	ILVariable_check(self, env, cctx);
	GenericType* ret = NULL;
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		ret = EvalILVariableLocal(self->Kind.Local, env, cctx);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		ret = EvalILVariableStatic(self->Kind.Static, env, cctx);
	}
	return ret;
}

char* ILVariableToString(ILVariable* self, Enviroment* env) {
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		return ILVariableLocalToString(self->Kind.Local, env);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		return ILVariableStaticToString(self->Kind.Static, env);
	}
	return NULL;
}

void DeleteILVariable(ILVariable * self) {
	//MEM_FREE(self->name);
	if(self->Type == ILVARIABLE_TYPE_LOCAL_T) {
		DeleteILVariableLocal(self->Kind.Local);
	} else if(self->Type == ILVARIABLE_TYPE_STATIC_T) {
		DeleteILVariableStatic(self->Kind.Static);
	}
	DeleteFQCNCache(self->FQCN);
	DeleteVector(self->TypeArgs, DeleteILFactor_typeargs);
	MEM_FREE(self);
}

//private
static void ILVariable_check(ILVariable* self, Enviroment* env, CallContext* cctx) {
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

static void ILVariable_check_instance(ILVariable* self, Enviroment* env, CallContext* cctx) {
	Namespace* cur = GetNamespaceCContext(cctx);
	class_* ctype = FindClassFromNamespace(cur, self->FQCN->Name);
	if(ctype == NULL) {
		ctype = FindClassFromNamespace(GetLangNamespace(), self->FQCN->Name);
	}
	//現在の名前空間から参照できるクラスがある場合
	if(ctype != NULL) {
		ILVariable_check_static(self, env, cctx);
	//ただのローカル変数の場合
	} else {
		ILVariable_local* lc = NewILVariableLocal(self->FQCN->Name);
		self->Type = ILVARIABLE_TYPE_LOCAL_T;
		//値を入れ替え
		lc->type_args = self->TypeArgs;
		self->TypeArgs = NULL;
		self->Kind.Local = lc;
	}
}

static void ILVariable_check_static(ILVariable* self, Enviroment* env, CallContext* cctx) {
	ILVariable_static* st = NewILVariableStatic();
	self->Type = ILVARIABLE_TYPE_STATIC_T;
	//値を入れ替え
	st->fqcn = self->FQCN;
	st->type_args = self->TypeArgs;
	self->FQCN = NULL;
	self->TypeArgs = NULL;
	self->Kind.Static = st;
}

static void DeleteILFactor_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}