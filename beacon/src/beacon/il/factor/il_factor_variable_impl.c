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
static void ILFactor_variable_check(ILFactor_variable* self, Enviroment* env, CallContext* cctx);
static void ILFactor_variable_check_instance(ILFactor_variable* self, Enviroment* env, CallContext* cctx);
static void ILFactor_variable_check_static(ILFactor_variable* self, Enviroment* env, CallContext* cctx);
static void DeleteILFactor_typeargs(VectorItem item);

ILFactor * WrapILVariable(ILFactor_variable * self) {
	ILFactor* ret = ILFactor_new(ILFACTOR_VARIABLE_T);
	ret->u.variable_ = self;
	return ret;
}

ILFactor_variable * MallocILVariable(const char* filename, int lineno) {
	ILFactor_variable* ret = (ILFactor_variable*)mem_malloc(sizeof(ILFactor_variable), filename, lineno);
	ret->fqcn = MallocFQCNCache(filename, lineno);
	ret->type_args = MallocVector(filename, lineno);
	ret->type = ILVARIABLE_TYPE_UNDEFINED_T;
	return ret;
}

void GenerateILVariable(ILFactor_variable * self, Enviroment* env, CallContext* cctx) {
	ILFactor_variable_check(self, env, cctx);
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		GenerateILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		GenerateILVariableStatic(self->u.static_, env, cctx);
	}
}

void LoadILVariable(ILFactor_variable * self, Enviroment * env, CallContext* cctx) {
	ILFactor_variable_check(self, env, cctx);
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		LoadILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		LoadILVariableStatic(self->u.static_, env, cctx);
	}
}

GenericType* EvalILVariable(ILFactor_variable * self, Enviroment * env, CallContext* cctx) {
	ILFactor_variable_check(self, env, cctx);
	GenericType* ret = NULL;
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		ret = EvalILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		ret = EvalILVariableStatic(self->u.static_, env, cctx);
	}
	return ret;
}

char* ILVariableToString(ILFactor_variable* self, Enviroment* env) {
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		return ILVariableLocalToString(self->u.local_, env);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		return ILVariableStaticToString(self->u.static_, env);
	}
	return NULL;
}

void DeleteILVariable(ILFactor_variable * self) {
	//MEM_FREE(self->name);
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		DeleteILVariableLocal(self->u.local_);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		DeleteILVariableStatic(self->u.static_);
	}
	DeleteFQCNCache(self->fqcn);
	DeleteVector(self->type_args, DeleteILFactor_typeargs);
	MEM_FREE(self);
}

//private
static void ILFactor_variable_check(ILFactor_variable* self, Enviroment* env, CallContext* cctx) {
	if(self->type != ILVARIABLE_TYPE_UNDEFINED_T) {
		return;
	}
	assert(self->fqcn != NULL);
	//hoge, foo のような文字列の場合
	if(self->fqcn->Scope->Length == 0) {
		ILFactor_variable_check_instance(self, env, cctx);
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->fqcn->Scope->Length > 0) {
		ILFactor_variable_check_static(self, env, cctx);
	}
}

static void ILFactor_variable_check_instance(ILFactor_variable* self, Enviroment* env, CallContext* cctx) {
	Namespace* cur = GetNamespaceCContext(cctx);
	class_* ctype = FindClassFromNamespace(cur, self->fqcn->Name);
	if(ctype == NULL) {
		ctype = FindClassFromNamespace(GetLangNamespace(), self->fqcn->Name);
	}
	//現在の名前空間から参照できるクラスがある場合
	if(ctype != NULL) {
		ILFactor_variable_check_static(self, env, cctx);
	//ただのローカル変数の場合
	} else {
		ILFactor_variable_local* lc = NewILVariableLocal(self->fqcn->Name);
		self->type = ILVARIABLE_TYPE_LOCAL_T;
		//値を入れ替え
		lc->type_args = self->type_args;
		self->type_args = NULL;
		self->u.local_ = lc;
	}
}

static void ILFactor_variable_check_static(ILFactor_variable* self, Enviroment* env, CallContext* cctx) {
	ILFactor_variable_static* st = NewILVariableStatic();
	self->type = ILVARIABLE_TYPE_STATIC_T;
	//値を入れ替え
	st->fqcn = self->fqcn;
	st->type_args = self->type_args;
	self->fqcn = NULL;
	self->type_args = NULL;
	self->u.static_ = st;
}

static void DeleteILFactor_typeargs(VectorItem item) {
	ILTypeArgument* e = (ILTypeArgument*)item;
	DeleteILTypeArgument(e);
}