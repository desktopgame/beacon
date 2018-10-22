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
static void CLILFQCNCache_impl(AST* afqcn, fqcn_cache* fqcn, int level);
static void CLILGenericCache_impl(AST* afqcn, generic_cache* dest);
static void CLILGenericCache_inner(AST* atype_args, generic_cache* dest);
static void CLILTypeParameter_rule(struct class_loader* self, struct AST* asource, Vector* dest);
static void ast_fqcn_flatten(AST* afqcn, Vector* dest);
static void CLILArgumentListImpl(class_loader* self, Vector* list, AST* asource);

void CLILFQCNCache(AST* afqcn, fqcn_cache* fqcn) {
	CLILFQCNCache_impl(afqcn, fqcn, 0);
}

void CLILGenericCache(AST* afqcn, generic_cache* dest) {
	if(afqcn->Tag == AST_FQCN_CLASS_NAME_T) {
		dest->fqcn->namev = afqcn->Attr.StringVValue;
		return;
	}
	CLILGenericCache_impl(afqcn, dest);
	fqcn_cache* body = dest->fqcn;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->namev == 0 &&
		body->scope_vec->Length > 0) {
		body->namev = (StringView)PopVector(body->scope_vec);
	}
}

void CLILTypenameList(class_loader * self, Vector * dst, AST* atypename_list) {
	if (IsBlankAST(atypename_list)) {
		return;
	}
	if (atypename_list->Tag == AST_TYPENAME_T) {
		generic_cache* e = NewGenericCache();
		//[typename [fqcn]]
		CLILGenericCache(atypename_list, e);
		PushVector(dst, e);
	} else if(atypename_list->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atypename_list->Children->Length; i++) {
			CLILTypenameList(self, dst, AtAST(atypename_list, i));
		}
	}
}


void CLILTypeParameter(class_loader* self, AST* asource, Vector* dest) {
	if (IsBlankAST(asource)) {
		return;
	}
	if (asource->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILTypeParameter(self, AtAST(asource, i), dest);
		}
		return;
	}
	assert(asource->Tag == AST_TYPE_PARAMETER_T ||
		   asource->Tag == AST_TYPE_IN_PARAMETER_T ||
		   asource->Tag == AST_TYPE_OUT_PARAMETER_T);
	AST* arule_list = FirstAST(asource);
	il_type_parameter* iltypeparam = NewILTypeParameter(asource->Attr.StringVValue);
	if (asource->Tag == AST_TYPE_IN_PARAMETER_T) iltypeparam->kind = il_TYPE_PARAMETER_KIND_IN_T;
	if (asource->Tag == AST_TYPE_OUT_PARAMETER_T) iltypeparam->kind = il_TYPE_PARAMETER_KIND_OUT_T;
	PushVector(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(IsBlankAST(arule_list));
}

void CLILTypeArgument(class_loader* self, AST* atype_args, Vector* dest) {
	if(IsBlankAST(atype_args)) {
		return;
	}
	if(atype_args->Tag == AST_TYPENAME_LIST_T) {
		for(int i=0; i<atype_args->Children->Length; i++) {
			AST* e = AtAST(atype_args, i);
			CLILTypeArgument(self, e, dest);
		}
	} else if(atype_args->Tag == AST_TYPENAME_T) {
		il_type_argument* iltype_arg = NewILTypeArgument();
		PushVector(dest, iltype_arg);
		CLILGenericCache(atype_args, iltype_arg->gcache);
	} else assert(false);
}

void CLILParameterList(class_loader* self, Vector* list, AST* asource) {
	if (asource->Tag == AST_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILParameterList(self, list, AtAST(asource, i));
		}
	} else if (asource->Tag == AST_PARAMETER_T) {
		AST* aGetTypeName = FirstAST(asource);
		AST* aaccess_name = SecondAST(asource);
		il_parameter* p = NewILParameter(aaccess_name->Attr.StringVValue);
		CLILGenericCache(aGetTypeName, p->fqcn);
		PushVector(list, p);
	}
}

void CLILArgumentList(class_loader* self, Vector* list, AST* asource) {
	CLILArgumentListImpl(self, list, asource);
}
//private
static void CLILFQCNCache_impl(AST* afqcn, fqcn_cache* fqcn, int level) {
	Vector* v = NewVector();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->Length; i++) {
		StringView S = (StringView)AtVector(v, i);
		if(i < v->Length - 1) {
			PushVector(fqcn->scope_vec, S);
		} else {
			fqcn->namev = S;
		}
	}
	DeleteVector(v, VectorDeleterOfNull);
}

static void CLILGenericCache_impl(AST* afqcn, generic_cache* dest) {
	fqcn_cache* body = dest->fqcn;
	//型引数を解析する
	if (afqcn->Tag == AST_TYPENAME_T) {
		AST* atype_args = SecondAST(afqcn);
		if (!IsBlankAST(atype_args)) {
			CLILGenericCache_inner(atype_args, dest);
		}
	}
	if (afqcn->Tag == AST_TYPENAME_T) {
		CLILGenericCache_impl(FirstAST(afqcn), dest);
		return;
	}
	if (afqcn->Tag == AST_FQCN_T ||
		afqcn->Tag == AST_FQCN_PART_LIST_T) {
		if (afqcn->Tag == AST_FQCN_PART_LIST_T &&
			afqcn->Children->Length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->Tag = AST_FQCN_CLASS_NAME_T;
			body->namev = afqcn->Attr.StringVValue;
			return;
		}
		for (int i = 0; i < afqcn->Children->Length; i++) {
			AST* c = AtAST(afqcn, i);
			CLILGenericCache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		PushVector(body->scope_vec, afqcn->Attr.StringVValue);
		afqcn->Tag = AST_FQCN_PART_T;
	}
}

static void CLILGenericCache_inner(AST* atype_args, generic_cache* dest) {
	if (atype_args->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atype_args->Children->Length; i++) {
			AST* e = AtAST(atype_args, i);
			CLILGenericCache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = NewGenericCache();
		CLILGenericCache(atype_args, newCache);
		PushVector(dest->type_args, newCache);
	}
}

static void CLILTypeParameter_rule(class_loader* self, AST* asource, Vector* dest) {
	assert(false);
	/*
	if (source->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < source->child_count; i++) {
			CLILTypeParameter_rule(self, AtAST(source, i), dest);
		}
	} else {
		if (source->Tag == AST_TYPENAME_T) {
			il_type_parameter_rule* rule = il_type_parameter_rule_new();
			rule->Tag = il_type_parameter_rule_polymorphic;
			rule->u.fqcn_ = NewGenericCache();
			CLILGenericCache(source, rule->u.fqcn_);
			PushVector(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(AST* afqcn, Vector* dest) {
	if(afqcn->Tag == AST_FQCN_PART_T) {
		PushVector(dest, afqcn->Attr.StringVValue);
	} else {
		for(int i=0; i<afqcn->Children->Length; i++) {
			ast_fqcn_flatten(AtAST(afqcn, i), dest);
		}
	}
}

static void CLILArgumentListImpl(class_loader* self, Vector* list, AST* asource) {
	if (asource->Tag == AST_ARGUMENT_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILArgumentListImpl(self, list, AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ARGUMENT_T) {
		AST* aprimary = FirstAST(asource);
		ILArgument* ilarg = NewILArgument();
		ilarg->Factor = CLILFactor(self, aprimary);
		PushVector(list, ilarg);
	}
}