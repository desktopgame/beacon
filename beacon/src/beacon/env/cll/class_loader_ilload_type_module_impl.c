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
static void CLIL_type_parameter_rule(struct class_loader* self, struct ast* asource, Vector* dest);
static void ast_fqcn_flatten(ast* afqcn, Vector* dest);
static void CLIL_argument_listImpl(class_loader* self, Vector* list, ast* asource);

void CLIL_fqcn_cache(ast* afqcn, fqcn_cache* fqcn) {
	CLIL_fqcn_cache_impl(afqcn, fqcn, 0);
}

void CLIL_generic_cache(ast* afqcn, generic_cache* dest) {
	if(afqcn->tag == ast_fqcn_class_name_T) {
		dest->fqcn->namev = afqcn->u.stringv_value;
		return;
	}
	CLIL_generic_cache_impl(afqcn, dest);
	fqcn_cache* body = dest->fqcn;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->namev == 0 &&
		body->scope_vec->length > 0) {
		body->namev = (string_view)PopVector(body->scope_vec);
	}
}

void CLIL_typename_list(class_loader * self, Vector * dst, ast * atypename_list) {
	if (ast_is_blank(atypename_list)) {
		return;
	}
	if (atypename_list->tag == ast_typename_T) {
		generic_cache* e = generic_cache_new();
		//[typename [fqcn]]
		CLIL_generic_cache(atypename_list, e);
		PushVector(dst, e);
	} else if(atypename_list->tag == ast_typename_list_T) {
		for (int i = 0; i < atypename_list->vchildren->length; i++) {
			CLIL_typename_list(self, dst, ast_at(atypename_list, i));
		}
	}
}


void CLIL_type_parameter(class_loader* self, ast* asource, Vector* dest) {
	if (ast_is_blank(asource)) {
		return;
	}
	if (asource->tag == ast_type_parameter_list_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_type_parameter(self, ast_at(asource, i), dest);
		}
		return;
	}
	assert(asource->tag == ast_type_parameter_T ||
		   asource->tag == ast_type_in_parameter_T ||
		   asource->tag == ast_type_out_parameter_T);
	ast* arule_list = ast_first(asource);
	il_type_parameter* iltypeparam = il_type_parameter_new(asource->u.stringv_value);
	if (asource->tag == ast_type_in_parameter_T) iltypeparam->kind = il_type_parameter_kind_in_T;
	if (asource->tag == ast_type_out_parameter_T) iltypeparam->kind = il_type_parameter_kind_out_T;
	PushVector(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(ast_is_blank(arule_list));
}

void CLIL_type_argument(class_loader* self, ast* atype_args, Vector* dest) {
	if(ast_is_blank(atype_args)) {
		return;
	}
	if(atype_args->tag == ast_typename_list_T) {
		for(int i=0; i<atype_args->vchildren->length; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_type_argument(self, e, dest);
		}
	} else if(atype_args->tag == ast_typename_T) {
		il_type_argument* iltype_arg = il_type_argument_new();
		PushVector(dest, iltype_arg);
		CLIL_generic_cache(atype_args, iltype_arg->gcache);
	} else assert(false);
}

void CLIL_parameter_list(class_loader* self, Vector* list, ast* asource) {
	if (asource->tag == ast_parameter_list_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_parameter_list(self, list, ast_at(asource, i));
		}
	} else if (asource->tag == ast_parameter_T) {
		ast* atype_name = ast_first(asource);
		ast* aaccess_name = ast_second(asource);
		il_parameter* p = il_parameter_new(aaccess_name->u.stringv_value);
		CLIL_generic_cache(atype_name, p->fqcn);
		PushVector(list, p);
	}
}

void CLIL_argument_list(class_loader* self, Vector* list, ast* asource) {
	CLIL_argument_listImpl(self, list, asource);
}
//private
static void CLIL_fqcn_cache_impl(ast* afqcn, fqcn_cache* fqcn, int level) {
	Vector* v = NewVector();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->length; i++) {
		string_view S = (string_view)AtVector(v, i);
		if(i < v->length - 1) {
			PushVector(fqcn->scope_vec, S);
		} else {
			fqcn->namev = S;
		}
	}
	DeleteVector(v, VectorDeleterOfNull);
}

static void CLIL_generic_cache_impl(ast* afqcn, generic_cache* dest) {
	fqcn_cache* body = dest->fqcn;
	//型引数を解析する
	if (afqcn->tag == ast_typename_T) {
		ast* atype_args = ast_second(afqcn);
		if (!ast_is_blank(atype_args)) {
			CLIL_generic_cache_inner(atype_args, dest);
		}
	}
	if (afqcn->tag == ast_typename_T) {
		CLIL_generic_cache_impl(ast_first(afqcn), dest);
		return;
	}
	if (afqcn->tag == ast_fqcn_T ||
		afqcn->tag == ast_fqcn_part_list_T) {
		if (afqcn->tag == ast_fqcn_part_list_T &&
			afqcn->vchildren->length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->tag = ast_fqcn_class_name_T;
			body->namev = afqcn->u.stringv_value;
			return;
		}
		for (int i = 0; i < afqcn->vchildren->length; i++) {
			ast* c = ast_at(afqcn, i);
			CLIL_generic_cache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		PushVector(body->scope_vec, afqcn->u.stringv_value);
		afqcn->tag = ast_fqcn_part_T;
	}
}

static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest) {
	if (atype_args->tag == ast_typename_list_T) {
		for (int i = 0; i < atype_args->vchildren->length; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_generic_cache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = generic_cache_new();
		CLIL_generic_cache(atype_args, newCache);
		PushVector(dest->type_args, newCache);
	}
}

static void CLIL_type_parameter_rule(class_loader* self, ast* asource, Vector* dest) {
	assert(false);
	/*
	if (source->tag == ast_type_parameter_list_T) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter_rule(self, ast_at(source, i), dest);
		}
	} else {
		if (source->tag == ast_typename_T) {
			il_type_parameter_rule* rule = il_type_parameter_rule_new();
			rule->tag = il_type_parameter_rule_polymorphic;
			rule->u.fqcn_ = generic_cache_new();
			CLIL_generic_cache(source, rule->u.fqcn_);
			PushVector(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(ast* afqcn, Vector* dest) {
	if(afqcn->tag == ast_fqcn_part_T) {
		PushVector(dest, afqcn->u.stringv_value);
	} else {
		for(int i=0; i<afqcn->vchildren->length; i++) {
			ast_fqcn_flatten(ast_at(afqcn, i), dest);
		}
	}
}

static void CLIL_argument_listImpl(class_loader* self, Vector* list, ast* asource) {
	if (asource->tag == ast_argument_list_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_argument_listImpl(self, list, ast_at(asource, i));
		}
	} else if (asource->tag == ast_argument_T) {
		ast* aprimary = ast_first(asource);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = CLIL_factor(self, aprimary);
		PushVector(list, ilarg);
	}
}