#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../util/mem.h"
#include "../../vm/symbol_entry.h"
#include <assert.h>
#include <string.h>

//proto
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, il_load_cache* cache);

il_factor * il_factor_wrap_variable(il_factor_variable * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_variable;
	ret->u.variable_ = self;
	return ret;
}

il_factor_variable * il_factor_variable_new() {
	il_factor_variable* ret = (il_factor_variable*)MEM_MALLOC(sizeof(il_factor_variable));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = vector_new();
	ret->type = ilvariable_type_undefined;
	return ret;
}

void il_factor_variable_dump(il_factor_variable * self, int depth) {
	text_putindent(depth);
	text_printf("variable ");
	fqcn_cache_print(self->fqcn);
	text_putline();
}

void il_factor_variable_generate(il_factor_variable * self, enviroment* env, il_load_cache* cache) {
	il_factor_variable_check(self, env, cache);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_generate(self->u.local_, env, cache);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_generate(self->u.static_, env, cache);
	}
}

void il_factor_variable_load(il_factor_variable * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
	il_factor_variable_check(self, env, cache);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_load(self->u.local_, env, cache, eh);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_load(self->u.static_, env, cache, eh);
	}
}

generic_type* il_factor_variable_eval(il_factor_variable * self, enviroment * env, il_load_cache* cache) {
	il_factor_variable_check(self, env, cache);
	if(self->type == ilvariable_type_local) {
		return il_factor_variable_local_eval(self->u.local_, env, cache);
	} else if(self->type == ilvariable_type_static) {
		return il_factor_variable_static_eval(self->u.static_, env, cache);
	}
	return NULL;
}

void il_factor_variable_delete(il_factor_variable * self) {
	//MEM_FREE(self->name);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_delete(self->u.local_);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_delete(self->u.static_);
	}
	MEM_FREE(self);
}

//private
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, il_load_cache* cache) {
	if(self->type != ilvariable_type_undefined) {
		return;
	}
	//hoge, foo のような文字列の場合
	if(self->fqcn->scope_vec->length == 0) {
		il_factor_variable_local* lc = il_factor_variable_local_new(self->fqcn->name);
		self->type = ilvariable_type_local;
		//値を入れ替え
		lc->entry = symbol_table_entry(env->sym_table, NULL, lc->name);
		lc->type_args = self->type_args;
		self->type_args = NULL;
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->fqcn->scope_vec->length > 0) {
		il_factor_variable_static* st = il_factor_variable_static_new();
		self->type = ilvariable_type_static;
		//値を入れ替え
		st->fqcn = self->fqcn;
		st->type_args = self->type_args;
		self->fqcn = NULL;
		self->type_args = NULL;
	}
}

il_factor_variable* il_factor_cast_variable(il_factor* fact) {
	assert(fact->type == ilfactor_variable);
	return fact->u.variable_;
}