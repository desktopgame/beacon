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
	if(afqcn->tag == AST_FQCN_CLASS_NAME_T) {
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
	if (IsBlankAST(atypename_list)) {
		return;
	}
	if (atypename_list->tag == AST_TYPENAME_T) {
		generic_cache* e = NewGenericCache();
		//[typename [fqcn]]
		CLIL_generic_cache(atypename_list, e);
		PushVector(dst, e);
	} else if(atypename_list->tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atypename_list->vchildren->length; i++) {
			CLIL_typename_list(self, dst, AtAST(atypename_list, i));
		}
	}
}


void CLIL_type_parameter(class_loader* self, ast* asource, Vector* dest) {
	if (IsBlankAST(asource)) {
		return;
	}
	if (asource->tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_type_parameter(self, AtAST(asource, i), dest);
		}
		return;
	}
	assert(asource->tag == AST_TYPE_PARAMETER_T ||
		   asource->tag == AST_TYPE_IN_PARAMETER_T ||
		   asource->tag == AST_TYPE_OUT_PARAMETER_T);
	ast* arule_list = FirstAST(asource);
	il_type_parameter* iltypeparam = NewILTypeParameter(asource->u.stringv_value);
	if (asource->tag == AST_TYPE_IN_PARAMETER_T) iltypeparam->kind = il_TYPE_PARAMETER_KIND_IN_T;
	if (asource->tag == AST_TYPE_OUT_PARAMETER_T) iltypeparam->kind = il_TYPE_PARAMETER_KIND_OUT_T;
	PushVector(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(IsBlankAST(arule_list));
}

void CLIL_type_argument(class_loader* self, ast* atype_args, Vector* dest) {
	if(IsBlankAST(atype_args)) {
		return;
	}
	if(atype_args->tag == AST_TYPENAME_LIST_T) {
		for(int i=0; i<atype_args->vchildren->length; i++) {
			ast* e = AtAST(atype_args, i);
			CLIL_type_argument(self, e, dest);
		}
	} else if(atype_args->tag == AST_TYPENAME_T) {
		il_type_argument* iltype_arg = NewILTypeArgument();
		PushVector(dest, iltype_arg);
		CLIL_generic_cache(atype_args, iltype_arg->gcache);
	} else assert(false);
}

void CLIL_parameter_list(class_loader* self, Vector* list, ast* asource) {
	if (asource->tag == AST_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_parameter_list(self, list, AtAST(asource, i));
		}
	} else if (asource->tag == AST_PARAMETER_T) {
		ast* atype_name = FirstAST(asource);
		ast* aaccess_name = SecondAST(asource);
		il_parameter* p = NewILParameter(aaccess_name->u.stringv_value);
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
	if (afqcn->tag == AST_TYPENAME_T) {
		ast* atype_args = SecondAST(afqcn);
		if (!IsBlankAST(atype_args)) {
			CLIL_generic_cache_inner(atype_args, dest);
		}
	}
	if (afqcn->tag == AST_TYPENAME_T) {
		CLIL_generic_cache_impl(FirstAST(afqcn), dest);
		return;
	}
	if (afqcn->tag == AST_FQCN_T ||
		afqcn->tag == AST_FQCN_PART_LIST_T) {
		if (afqcn->tag == AST_FQCN_PART_LIST_T &&
			afqcn->vchildren->length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->tag = AST_FQCN_CLASS_NAME_T;
			body->namev = afqcn->u.stringv_value;
			return;
		}
		for (int i = 0; i < afqcn->vchildren->length; i++) {
			ast* c = AtAST(afqcn, i);
			CLIL_generic_cache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		PushVector(body->scope_vec, afqcn->u.stringv_value);
		afqcn->tag = AST_FQCN_PART_T;
	}
}

static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest) {
	if (atype_args->tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atype_args->vchildren->length; i++) {
			ast* e = AtAST(atype_args, i);
			CLIL_generic_cache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = NewGenericCache();
		CLIL_generic_cache(atype_args, newCache);
		PushVector(dest->type_args, newCache);
	}
}

static void CLIL_type_parameter_rule(class_loader* self, ast* asource, Vector* dest) {
	assert(false);
	/*
	if (source->tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter_rule(self, AtAST(source, i), dest);
		}
	} else {
		if (source->tag == AST_TYPENAME_T) {
			il_type_parameter_rule* rule = il_type_parameter_rule_new();
			rule->tag = il_type_parameter_rule_polymorphic;
			rule->u.fqcn_ = NewGenericCache();
			CLIL_generic_cache(source, rule->u.fqcn_);
			PushVector(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(ast* afqcn, Vector* dest) {
	if(afqcn->tag == AST_FQCN_PART_T) {
		PushVector(dest, afqcn->u.stringv_value);
	} else {
		for(int i=0; i<afqcn->vchildren->length; i++) {
			ast_fqcn_flatten(AtAST(afqcn, i), dest);
		}
	}
}

static void CLIL_argument_listImpl(class_loader* self, Vector* list, ast* asource) {
	if (asource->tag == AST_ARGUMENT_LIST_T) {
		for (int i = 0; i < asource->vchildren->length; i++) {
			CLIL_argument_listImpl(self, list, AtAST(asource, i));
		}
	} else if (asource->tag == AST_ARGUMENT_T) {
		ast* aprimary = FirstAST(asource);
		il_argument* ilarg = NewILArgument();
		ilarg->factor = CLIL_factor(self, aprimary);
		PushVector(list, ilarg);
	}
}