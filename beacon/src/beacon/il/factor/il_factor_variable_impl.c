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
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, call_context* cctx);
static void il_factor_variable_check_instance(il_factor_variable* self, enviroment* env, call_context* cctx);
static void il_factor_variable_check_static(il_factor_variable* self, enviroment* env, call_context* cctx);
static void DeleteILFactor_typeargs(VectorItem item);

il_factor * WrapILVariable(il_factor_variable * self) {
	il_factor* ret = il_factor_new(ILFACTOR_VARIABLE_T);
	ret->u.variable_ = self;
	return ret;
}

il_factor_variable * MallocILVariable(const char* filename, int lineno) {
	il_factor_variable* ret = (il_factor_variable*)mem_malloc(sizeof(il_factor_variable), filename, lineno);
	ret->fqcn = MallocFQCNCache(filename, lineno);
	ret->type_args = MallocVector(filename, lineno);
	ret->type = ILVARIABLE_TYPE_UNDEFINED_T;
	return ret;
}

void GenerateILVariable(il_factor_variable * self, enviroment* env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		GenerateILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		GenerateILVariableStatic(self->u.static_, env, cctx);
	}
}

void LoadILVariable(il_factor_variable * self, enviroment * env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		LoadILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		LoadILVariableStatic(self->u.static_, env, cctx);
	}
}

generic_type* EvalILVariable(il_factor_variable * self, enviroment * env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	generic_type* ret = NULL;
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		ret = EvalILVariableLocal(self->u.local_, env, cctx);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		ret = EvalILVariableStatic(self->u.static_, env, cctx);
	}
	return ret;
}

char* ILVariableToString(il_factor_variable* self, enviroment* env) {
	if(self->type == ILVARIABLE_TYPE_LOCAL_T) {
		return ILVariableLocalToString(self->u.local_, env);
	} else if(self->type == ILVARIABLE_TYPE_STATIC_T) {
		return ILVariableStaticToString(self->u.static_, env);
	}
	return NULL;
}

void DeleteILVariable(il_factor_variable * self) {
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
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, call_context* cctx) {
	if(self->type != ILVARIABLE_TYPE_UNDEFINED_T) {
		return;
	}
	assert(self->fqcn != NULL);
	//hoge, foo のような文字列の場合
	if(self->fqcn->scope_vec->Length == 0) {
		il_factor_variable_check_instance(self, env, cctx);
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->fqcn->scope_vec->Length > 0) {
		il_factor_variable_check_static(self, env, cctx);
	}
}

static void il_factor_variable_check_instance(il_factor_variable* self, enviroment* env, call_context* cctx) {
	namespace_* cur = GetNamespaceCContext(cctx);
	class_* ctype = FindClassFromNamespace(cur, self->fqcn->namev);
	if(ctype == NULL) {
		ctype = FindClassFromNamespace(GetLangNamespace(), self->fqcn->namev);
	}
	//現在の名前空間から参照できるクラスがある場合
	if(ctype != NULL) {
		il_factor_variable_check_static(self, env, cctx);
	//ただのローカル変数の場合
	} else {
		il_factor_variable_local* lc = NewILVariableLocal(self->fqcn->namev);
		self->type = ILVARIABLE_TYPE_LOCAL_T;
		//値を入れ替え
		lc->type_args = self->type_args;
		self->type_args = NULL;
		self->u.local_ = lc;
	}
}

static void il_factor_variable_check_static(il_factor_variable* self, enviroment* env, call_context* cctx) {
	il_factor_variable_static* st = NewILVariableStatic();
	self->type = ILVARIABLE_TYPE_STATIC_T;
	//値を入れ替え
	st->fqcn = self->fqcn;
	st->type_args = self->type_args;
	self->fqcn = NULL;
	self->type_args = NULL;
	self->u.static_ = st;
}

static void DeleteILFactor_typeargs(VectorItem item) {
	il_type_argument* e = (il_type_argument*)item;
	DeleteILTypeArgument(e);
}