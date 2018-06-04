#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "../../ast/ast.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../../util/text.h"

#include "../class_loader.h"
//#include "../../il/il_type_parameter_rule.h"
#include "../../il/il_type_parameter.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLIL_fqcn_cache_impl(ast* afqcn, fqcn_cache* fqcn, int level);
static void CLIL_generic_cache_impl(ast* fqcn, generic_cache* dest);
static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest);
static void CLIL_type_parameter_rule(struct class_loader* self, struct ast* source, vector* dest);
static void ast_fqcn_flatten(ast* afqcn, vector* dest);

void CLIL_fqcn_cache(ast* afqcn, fqcn_cache* fqcn) {
	CLIL_fqcn_cache_impl(afqcn, fqcn, 0);
}

void CLIL_generic_cache(ast* fqcn, generic_cache* dest) {
	if(fqcn->tag == ast_fqcn_class_name) {
		dest->fqcn->name = text_strdup(fqcn->u.string_value);
		return;
	}
	CLIL_generic_cache_impl(fqcn, dest);
	fqcn_cache* body = dest->fqcn;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->name == NULL &&
		body->scope_vec->length > 0) {
		body->name = (char*)vector_pop(body->scope_vec);
	}
}

void CLIL_typename_list(class_loader * self, vector * dst, ast * typename_list) {
	if (ast_is_blank(typename_list)) {
		return;
	}
	if (typename_list->tag == ast_typename) {
		generic_cache* e = generic_cache_new();
		//[typename [fqcn]]
		CLIL_generic_cache(typename_list, e);
		vector_push(dst, e);
	} else if(typename_list->tag == ast_typename_list) {
		for (int i = 0; i < typename_list->child_count; i++) {
			CLIL_typename_list(self, dst, ast_at(typename_list, i));
		}
	}
}


void CLIL_type_parameter(class_loader* self, ast* source, vector* dest) {
	if (ast_is_blank(source)) {
		return;
	}
	if (source->tag == ast_type_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter(self, ast_at(source, i), dest);
		}
		return;
	}
	assert(source->tag == ast_type_parameter ||
		   source->tag == ast_type_in_parameter ||
		   source->tag == ast_type_out_parameter);
	ast* arule_list = ast_first(source);
	il_type_parameter* iltypeparam = il_type_parameter_new(source->u.string_value);
	if (source->tag == ast_type_in_parameter) iltypeparam->kind = il_type_parameter_kind_in;
	if (source->tag == ast_type_out_parameter) iltypeparam->kind = il_type_parameter_kind_out;
	vector_push(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(ast_is_blank(arule_list));
}

void CLIL_type_argument(class_loader* self, ast* atype_args, vector* dest) {
	if(ast_is_blank(atype_args)) {
		return;
	}
	if(atype_args->tag == ast_typename_list) {
		for(int i=0; i<atype_args->child_count; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_type_argument(self, e, dest);
		}
	} else if(atype_args->tag == ast_typename) {
		il_type_argument* iltype_arg = il_type_argument_new();
		vector_push(dest, iltype_arg);
		CLIL_generic_cache(atype_args, iltype_arg->gcache);
	} else assert(false);
}

void CLIL_parameter_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_parameter_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_parameter) {
		ast* type_name = ast_first(source);
		ast* access_name = ast_second(source);
		il_parameter* p = il_parameter_new(access_name->u.string_value);
		CLIL_generic_cache(type_name, p->fqcn);
		vector_push(list, p);
	}
}

void CLIL_argument_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_argument_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_argument_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_argument) {
		ast* primary = ast_first(source);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = CLIL_factor(self, primary);
		vector_push(list, ilarg);
	}
}
//private
static void CLIL_fqcn_cache_impl(ast* afqcn, fqcn_cache* fqcn, int level) {
	vector* v = vector_new();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->length; i++) {
		char* S = text_strdup(vector_at(v, i));
		if(i < v->length - 1) {
			vector_push(fqcn->scope_vec, S);
		} else {
			fqcn->name = S;
		}
	}
	vector_delete(v, vector_deleter_null);
}

static void CLIL_generic_cache_impl(ast* fqcn, generic_cache* dest) {
	fqcn_cache* body = dest->fqcn;
	//型引数を解析する
	if (fqcn->tag == ast_typename) {
		ast* atype_args = ast_second(fqcn);
		if (!ast_is_blank(atype_args)) {
			CLIL_generic_cache_inner(atype_args, dest);
		}
	}
	if (fqcn->tag == ast_typename) {
		CLIL_generic_cache_impl(ast_first(fqcn), dest);
		return;
	}
	if (fqcn->tag == ast_fqcn ||
		fqcn->tag == ast_fqcn_part_list) {
		if (fqcn->tag == ast_fqcn_part_list &&
			fqcn->child_count == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			fqcn->tag = ast_fqcn_class_name;
			body->name = text_strdup(fqcn->u.string_value);
			return;
		}
		for (int i = 0; i < fqcn->child_count; i++) {
			ast* c = ast_at(fqcn, i);
			CLIL_generic_cache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		vector_push(body->scope_vec, text_strdup(fqcn->u.string_value));
		fqcn->tag = ast_fqcn_part;
	}
}

static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest) {
	if (atype_args->tag == ast_typename_list) {
		for (int i = 0; i < atype_args->child_count; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_generic_cache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = generic_cache_new();
		CLIL_generic_cache(atype_args, newCache);
		vector_push(dest->type_args, newCache);
	}
}

static void CLIL_type_parameter_rule(class_loader* self, ast* source, vector* dest) {
	assert(false);
	/*
	if (source->tag == ast_type_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter_rule(self, ast_at(source, i), dest);
		}
	} else {
		if (source->tag == ast_typename) {
			il_type_parameter_rule* rule = il_type_parameter_rule_new();
			rule->tag = il_type_parameter_rule_polymorphic;
			rule->u.fqcn_ = generic_cache_new();
			CLIL_generic_cache(source, rule->u.fqcn_);
			vector_push(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(ast* afqcn, vector* dest) {
	if(afqcn->tag == ast_fqcn_part) {
		vector_push(dest, afqcn->u.string_value);
	} else {
		for(int i=0; i<afqcn->child_count; i++) {
			ast_fqcn_flatten(ast_at(afqcn, i), dest);
		}
	}
}