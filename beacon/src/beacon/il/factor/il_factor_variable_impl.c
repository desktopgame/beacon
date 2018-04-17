#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../il_type_argument.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../util/mem.h"
#include "../../util/xassert.h"
#include "../../vm/symbol_entry.h"
#include <assert.h>
#include <string.h>

//proto
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, il_context* ilctx);
static void il_factor_delete_typeargs(vector_item item);

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

void il_factor_variable_generate(il_factor_variable * self, enviroment* env, il_context* ilctx) {
	il_factor_variable_check(self, env, ilctx);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_generate(self->u.local_, env, ilctx);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_generate(self->u.static_, env, ilctx);
	}
}

void il_factor_variable_load(il_factor_variable * self, enviroment * env, il_context* ilctx, il_ehandler * eh) {
	il_factor_variable_check(self, env, ilctx);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_load(self->u.local_, env, ilctx, eh);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_load(self->u.static_, env, ilctx, eh);
	}
}

generic_type* il_factor_variable_eval(il_factor_variable * self, enviroment * env, il_context* ilctx) {
	il_factor_variable_check(self, env, ilctx);
	generic_type* ret = NULL;
	if(self->type == ilvariable_type_local) {
		ret = il_factor_variable_local_eval(self->u.local_, env, ilctx);
	} else if(self->type == ilvariable_type_static) {
		ret = il_factor_variable_static_eval(self->u.static_, env, ilctx);
	}
	generic_type_validate(ret);
	return ret;
}

void il_factor_variable_delete(il_factor_variable * self) {
	//MEM_FREE(self->name);
	if(self->type == ilvariable_type_local) {
		il_factor_variable_local_delete(self->u.local_);
	} else if(self->type == ilvariable_type_static) {
		il_factor_variable_static_delete(self->u.static_);
	} else if(self->type == ilvariable_type_undefined) {
		vector_delete(self->type_args, il_factor_delete_typeargs);
	}
	fqcn_cache_delete(self->fqcn);
	MEM_FREE(self);
}

//private
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, il_context* ilctx) {
	if(self->type != ilvariable_type_undefined) {
		return;
	}
	assert(self->fqcn != NULL);
	//hoge, foo のような文字列の場合
	if(self->fqcn->scope_vec->length == 0) {
		namespace_* cur = il_context_namespace(ilctx);
		class_* ctype = namespace_get_class(cur, self->fqcn->name);
		if(ctype == NULL) {
			ctype = namespace_get_class(namespace_lang(), self->fqcn->name);
		}
		//現在の名前空間から参照できるクラスがある場合
		if(ctype != NULL) {
			//FIXME:すぐ下のところからコピペ
			il_factor_variable_static* st = il_factor_variable_static_new();
			self->type = ilvariable_type_static;
			//値を入れ替え
			st->fqcn = self->fqcn;
			st->type_args = self->type_args;
			self->fqcn = NULL;
			self->type_args = NULL;
			self->u.static_ = st;
		//ただのローカル変数の場合
		} else {
			il_factor_variable_local* lc = il_factor_variable_local_new(self->fqcn->name);
			self->type = ilvariable_type_local;
			//値を入れ替え
			//lc->entry = symbol_table_entry(env->sym_table, NULL, lc->name);
			lc->type_args = self->type_args;
			self->type_args = NULL;
			self->u.local_ = lc;
		}
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->fqcn->scope_vec->length > 0) {
		class_* cls = TYPE2CLASS((type*)vector_top(ilctx->type_vec));
		il_factor_variable_static* st = il_factor_variable_static_new();
		self->type = ilvariable_type_static;
		//値を入れ替え
		st->fqcn = self->fqcn;
		st->type_args = self->type_args;
		self->fqcn = NULL;
		self->type_args = NULL;
		self->u.static_ = st;
	}
}

static void il_factor_delete_typeargs(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

il_factor_variable* il_factor_cast_variable(il_factor* fact) {
	assert(fact->type == ilfactor_variable);
	return fact->u.variable_;
}