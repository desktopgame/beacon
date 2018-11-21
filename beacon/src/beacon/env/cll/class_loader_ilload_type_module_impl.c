#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include "../../ast/ast.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../../util/text.h"

#include "../class_loader.h"
//#include "../../il/ILTypeParameter_rule.h"
#include "../../il/il_type_parameter.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLILFQCNCache_impl(bc_AST* afqcn, bc_FQCNCache* fqcn, int level);
static void CLILGenericCache_impl(bc_AST* afqcn, bc_GenericCache* dest);
static void CLILGenericCache_inner(bc_AST* atype_args, bc_GenericCache* dest);
static void CLILTypeParameter_rule(struct bc_ClassLoader* self, struct bc_AST* asource, bc_Vector* dest);
static void ast_fqcn_flatten(bc_AST* afqcn, bc_Vector* dest);
static void CLILArgumentListImpl(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource);

void CLILFQCNCache(bc_AST* afqcn, bc_FQCNCache* fqcn) {
	CLILFQCNCache_impl(afqcn, fqcn, 0);
}

void CLILGenericCache(bc_AST* afqcn, bc_GenericCache* dest) {
	if(afqcn->Tag == AST_FQCN_CLASS_NAME_T) {
		dest->FQCN->Name = afqcn->Attr.StringVValue;
		return;
	}
	CLILGenericCache_impl(afqcn, dest);
	bc_FQCNCache* body = dest->FQCN;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->Name == 0 &&
		body->Scope->Length > 0) {
		body->Name = (bc_StringView)bc_PopVector(body->Scope);
	}
}

void CLILTypenameList(bc_ClassLoader * self, bc_Vector * dst, bc_AST* atypename_list) {
	if (bc_IsBlankAST(atypename_list)) {
		return;
	}
	if (atypename_list->Tag == AST_TYPENAME_T) {
		bc_GenericCache* e = bc_NewGenericCache();
		//[typename [fqcn]]
		CLILGenericCache(atypename_list, e);
		bc_PushVector(dst, e);
	} else if(atypename_list->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atypename_list->Children->Length; i++) {
			CLILTypenameList(self, dst, bc_AtAST(atypename_list, i));
		}
	}
}


void CLILTypeParameter(bc_ClassLoader* self, bc_AST* asource, bc_Vector* dest) {
	if (bc_IsBlankAST(asource)) {
		return;
	}
	if (asource->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILTypeParameter(self, bc_AtAST(asource, i), dest);
		}
		return;
	}
	assert(asource->Tag == AST_TYPE_PARAMETER_T ||
		   asource->Tag == AST_TYPE_IN_PARAMETER_T ||
		   asource->Tag == AST_TYPE_OUT_PARAMETER_T);
	bc_AST* arule_list = bc_FirstAST(asource);
	bc_ILTypeParameter* iltypeparam = bc_NewILTypeParameter(asource->Attr.StringVValue);
	if (asource->Tag == AST_TYPE_IN_PARAMETER_T) iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_IN_T;
	if (asource->Tag == AST_TYPE_OUT_PARAMETER_T) iltypeparam->Tag = IL_TYPE_PARAMETER_KIND_OUT_T;
	bc_PushVector(dest, iltypeparam);
	//制約があるならそれも設定
	//制約はとりあえずなしで
	assert(bc_IsBlankAST(arule_list));
}

void CLILTypeArgument(bc_ClassLoader* self, bc_AST* atype_args, bc_Vector* dest) {
	if(bc_IsBlankAST(atype_args)) {
		return;
	}
	if(atype_args->Tag == AST_TYPENAME_LIST_T) {
		for(int i=0; i<atype_args->Children->Length; i++) {
			bc_AST* e = bc_AtAST(atype_args, i);
			CLILTypeArgument(self, e, dest);
		}
	} else if(atype_args->Tag == AST_TYPENAME_T) {
		bc_ILTypeArgument* iltype_arg = bc_NewILTypeArgument();
		bc_PushVector(dest, iltype_arg);
		CLILGenericCache(atype_args, iltype_arg->GCache);
	} else assert(false);
}

void CLILParameterList(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource) {
	if (asource->Tag == AST_PARAMETER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILParameterList(self, list, bc_AtAST(asource, i));
		}
	} else if (asource->Tag == AST_PARAMETER_T) {
		bc_AST* aGetTypeName = bc_FirstAST(asource);
		bc_AST* aaccess_name = bc_SecondAST(asource);
		bc_ILParameter* p = bc_NewILParameter(aaccess_name->Attr.StringVValue);
		CLILGenericCache(aGetTypeName, p->GCache);
		bc_PushVector(list, p);
	}
}

void CLILArgumentList(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource) {
	CLILArgumentListImpl(self, list, asource);
}
//private
static void CLILFQCNCache_impl(bc_AST* afqcn, bc_FQCNCache* fqcn, int level) {
	bc_Vector* v = bc_NewVector();
	ast_fqcn_flatten(afqcn, v);
	for(int i=0; i<v->Length; i++) {
		bc_StringView S = (bc_StringView)bc_AtVector(v, i);
		if(i < v->Length - 1) {
			bc_PushVector(fqcn->Scope, S);
		} else {
			fqcn->Name = S;
		}
	}
	bc_DeleteVector(v, bc_VectorDeleterOfNull);
}

static void CLILGenericCache_impl(bc_AST* afqcn, bc_GenericCache* dest) {
	bc_FQCNCache* body = dest->FQCN;
	//型引数を解析する
	if (afqcn->Tag == AST_TYPENAME_T) {
		bc_AST* atype_args = bc_SecondAST(afqcn);
		if (!bc_IsBlankAST(atype_args)) {
			CLILGenericCache_inner(atype_args, dest);
		}
	}
	if (afqcn->Tag == AST_TYPENAME_T) {
		CLILGenericCache_impl(bc_FirstAST(afqcn), dest);
		return;
	}
	if (afqcn->Tag == AST_FQCN_T ||
		afqcn->Tag == AST_FQCN_PART_LIST_T) {
		if (afqcn->Tag == AST_FQCN_PART_LIST_T &&
			afqcn->Children->Length == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->Tag = AST_FQCN_CLASS_NAME_T;
			body->Name = afqcn->Attr.StringVValue;
			return;
		}
		for (int i = 0; i < afqcn->Children->Length; i++) {
			bc_AST* c = bc_AtAST(afqcn, i);
			CLILGenericCache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		bc_PushVector(body->Scope, afqcn->Attr.StringVValue);
		afqcn->Tag = AST_FQCN_PART_T;
	}
}

static void CLILGenericCache_inner(bc_AST* atype_args, bc_GenericCache* dest) {
	if (atype_args->Tag == AST_TYPENAME_LIST_T) {
		for (int i = 0; i < atype_args->Children->Length; i++) {
			bc_AST* e = bc_AtAST(atype_args, i);
			CLILGenericCache_inner(e, dest);
		}
	} else {
		bc_GenericCache* newCache = bc_NewGenericCache();
		CLILGenericCache(atype_args, newCache);
		bc_PushVector(dest->TypeArgs, newCache);
	}
}

static void CLILTypeParameter_rule(bc_ClassLoader* self, bc_AST* asource, bc_Vector* dest) {
	assert(false);
	/*
	if (source->Tag == AST_TYPE_PARAMETER_LIST_T) {
		for (int i = 0; i < source->child_count; i++) {
			CLILTypeParameter_rule(self, AtAST(source, i), dest);
		}
	} else {
		if (source->Tag == AST_TYPENAME_T) {
			ILTypeParameter_rule* rule = ILTypeParameter_rule_new();
			rule->Tag = ILTypeParameter_rule_polymorphic;
			rule->u.fqcn_ = NewGenericCache();
			CLILGenericCache(source, rule->u.fqcn_);
			PushVector(dest, rule);
		}
	}
	*/
}

static void ast_fqcn_flatten(bc_AST* afqcn, bc_Vector* dest) {
	if(afqcn->Tag == AST_FQCN_PART_T) {
		bc_PushVector(dest, afqcn->Attr.StringVValue);
	} else {
		for(int i=0; i<afqcn->Children->Length; i++) {
			ast_fqcn_flatten(bc_AtAST(afqcn, i), dest);
		}
	}
}

static void CLILArgumentListImpl(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource) {
	if (asource->Tag == AST_ARGUMENT_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			CLILArgumentListImpl(self, list, bc_AtAST(asource, i));
		}
	} else if (asource->Tag == AST_ARGUMENT_T) {
		bc_AST* aprimary = bc_FirstAST(asource);
		bc_ILArgument* ilarg = bc_NewILArgument();
		ilarg->Factor = CLILFactor(self, aprimary);
		bc_PushVector(list, ilarg);
	}
}