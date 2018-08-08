#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
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
static void CLIL_generic_cache_impl(ast* afqcn, generic_cache* dest);
static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest);
static void CLIL_type_parameter_rule(struct class_loader* self, struct ast* asource, vector* dest);
static void ast_fqcn_flatten(ast* afqcn, vector* dest);
static void CLIL_argument_listImpl(class_loader* self, vector* list, ast* asource);

void CLIL_fqcn_cache(ast* afqcn, fqcn_cache* fqcn) {
	CLIL_fqcn_cache_impl(afqcn, fqcn, 0);
}

void CLIL_generic_cache(ast* afqcn, generic_cache* dest) {
	if(afqcn->tag == ast_fqcn_class_name) {
		dest->fqcn->namev = afqcn->u.stringv_value;
		return;
	}
	CLIL_generic_cache_impl(afqcn, dest);
	fqcn_cache* body = dest->fqcn;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->namev == 0 &&
		body->scope_vec->length > 0) {
		body->namev = (string_view)vector_pop(body->scope_vec);
	}
}

void CLIL_typename_list(class_loader * self, vector * dst, ast * atypename_list) {
	if (ast_is_blank(atypename_list)) {
		return;
	}
	if (atypename_list->tag == ast_typename) {
		generic_cache* e = generic_cache_new();
		//[typename [fqcn]]
		CLIL_generic_cache(atypename_list, e);
		vector_push(dst, e);
	} else if(atypename_list->tag == ast_typename_list) {
		for (int i = 0; i < atypename_list->vchildren->length; i++) {
			CLIL_typename_list(self, dst, ast_at(atypename_list, i));
		}
	}
}


void CLIL_type_parameter(class_loader* self, ast* asource, vector* dest) {
	if (ast_is_blank(asource)) {
		return;
	}
	if (asource->tag == ast_type_parameter_list) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_type_parameter(self, ast_at(asource, i), dest);
		}
		return;
	}
	assert(asource->tag == ast_type_parameter ||
		   asource->tag == ast_type_in_parameter ||
		   asource->tag == ast_type_out_parameter);
	ast* arule_list = ast_first(asource);
	il_type_parameter* iltypeparam = il_type_parameter_new(asource->u.stringv_value);
	if (asource->tag == ast_type_in_parameter) iltypeparam->kind = il_type_parameter_kind_in;
	if (asource->tag == ast_type_out_parameter) iltypeparam->kind = il_type_parameter_kind_out;
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
		for(int i=0; i<atype_args->vchildren->length; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_type_argument(self, e, dest);
		}
	} else if(atype_args->tag == ast_typename) {
		il_type_argument* iltype_arg = il_type_argument_new();
		vector_push(dest, iltype_arg);
		CLIL_generic_cache(atype_args, iltype_arg->gcache);
	} else assert(false);
}

void CLIL_parameter_list(class_loader* self, vector* list, ast* asource) {
	if (asource->tag == ast_parameter_list) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_parameter_list(self, list, ast_at(asource, i));
		}
	} else if (asource->tag == ast_parameter) {
		ast* atype_name = ast_first(asource);
		ast* aaccess_name = ast_second(asource);
		il_parameter* p = il_parameter_new(aaccess_name->u.stringv_value);
		CLIL_generic_cache(atype_name, p->fqcn);
		vector_push(list, p);
	}
}

void CLIL_argument_list(class_loader* self, vector* list, ast* asource) {
	CLIL_argument_listImpl(self, list, asource);
	//ラムダに自分が引数列の中で何番目であるかを教える
	for(int i=0; i<list->length; i++) {
		il_argument* e = (il_argument*)vector_at(list, i);
		il_factor* f = e->factor;
		if(f->type == ilfactor_lambda) {
			il_factor_lambda* lambda = f->u.lambda_;
			lambda->offset = i;
		}
	}
}
//private
static void CLIL_fqcn_cache_impl(ast* afqcn, fqcn_cache* fqcn, int level) {
	vector* v = vector_new();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->length; i++) {
		string_view S = (string_view)vector_at(v, i);
		if(i < v->length - 1) {
			vector_push(fqcn->scope_vec, S);
		} else {
			fqcn->namev = S;
		}
	}
	vector_delete(v, vector_deleter_null);
}

static void CLIL_generic_cache_impl(ast* afqcn, generic_cache* dest) {
	fqcn_cache* body = dest->fqcn;
	//型引数を解析する
	if (afqcn->tag == ast_typename) {
		ast* atype_args = ast_second(afqcn);
		if (!ast_is_blank(atype_args)) {
			CLIL_generic_cache_inner(atype_args, dest);
		}
	}
	if (afqcn->tag == ast_typename) {
		CLIL_generic_cache_impl(ast_first(afqcn), dest);
		return;
	}
	if (afqcn->tag == ast_fqcn ||
		afqcn->tag == ast_fqcn_part_list) {
		if (afqcn->tag == ast_fqcn_part_list &&
			afqcn->vchildren->length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->tag = ast_fqcn_class_name;
			body->namev = afqcn->u.stringv_value;
			return;
		}
		for (int i = 0; i < afqcn->vchildren->length; i++) {
			ast* c = ast_at(afqcn, i);
			CLIL_generic_cache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		vector_push(body->scope_vec, afqcn->u.stringv_value);
		afqcn->tag = ast_fqcn_part;
	}
}

static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest) {
	if (atype_args->tag == ast_typename_list) {
		for (int i = 0; i < atype_args->vchildren->length; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_generic_cache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = generic_cache_new();
		CLIL_generic_cache(atype_args, newCache);
		vector_push(dest->type_args, newCache);
	}
}

static void CLIL_type_parameter_rule(class_loader* self, ast* asource, vector* dest) {
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
		vector_push(dest, afqcn->u.stringv_value);
	} else {
		for(int i=0; i<afqcn->vchildren->length; i++) {
			ast_fqcn_flatten(ast_at(afqcn, i), dest);
		}
	}
}

static void CLIL_argument_listImpl(class_loader* self, vector* list, ast* asource) {
	if (asource->tag == ast_argument_list) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_argument_listImpl(self, list, ast_at(asource, i));
		}
	} else if (asource->tag == ast_argument) {
		ast* aprimary = ast_first(asource);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = CLIL_factor(self, aprimary);
		vector_push(list, ilarg);
	} else if(asource->tag == ast_lambda) {
		//ラムダは実引数列にしかおけない仕様
		ast* aparam_list = ast_first(asource);
		ast* areturn = ast_second(asource);
		ast* abody = ast_at(asource, 2);
		il_factor_lambda* lbd = il_factor_lambda_new();
		CLIL_parameter_list(self, lbd->parameter_vec, aparam_list);
		CLIL_generic_cache(areturn, lbd->return_gtype);
		CLIL_body(self,lbd->statement_vec, abody);
		//ラムダを実引数でラップする
		il_argument* ilarg = il_argument_new();
		ilarg->factor = il_factor_wrap_lambda(lbd);
		vector_push(list, ilarg);
	}
}