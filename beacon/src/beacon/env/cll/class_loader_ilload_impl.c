#include "class_loader_ilload_impl.h"
#include "../../il/il_type_interface.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_field.h"
#include "../../il/il_import.h"
#include "../../il/il_function.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_parameter.h"
#include "../../il/il_argument.h"
#include "../../il/il_stmt_interface.h"
#include "../../il/il_stmt_impl.h"
#include "../../il/il_type_argument.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
//
//ilload
//
#include "../../il/il_type_parameter.h"
//#include "../../il/ILTypeParameter_rule.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include "class_loader_ilload_member_module_impl.h"

//proto

/**
 * トップレベルの関数宣言を IL に変換します.
 * @param self
 * @param source
 */
static void class_loader_ilload_function(class_loader* self, AST* asource);

/**
 * インポートの一覧を IL に変換します.
 * @param self
 * @param source
 */
static void class_loader_ilload_import_list(class_loader* self, AST* asource);

/**
 * インポート宣言を IL に変換します.
 * @param self
 * @param import_decl
 */
static void class_loader_ilload_import(class_loader* self, AST* aimport_decl);

/**
 * 名前空間とその内側のエントリ全てを IL に変換します.
 * @param self
 * @param parent
 * @param Namespacedecl
 */
static void class_loader_ilload_namespace(class_loader* self, Vector* parent, AST* aNamespacedecl);

/**
 * 名前空間のパス(A.B.C)を解析します.
 * デバッグ用の関数で、今は特に何も行いません。
 * @param self
 * @param Namespacepath
 * @param Namespacebody
 */
static void class_loader_ilload_Namespacepath_recursive(class_loader* self, AST* aNamespacepath, AST* Namespacebody);

/**
 * 名前空間(またはそのリスト)を IL に変換します.
 * @param a
 * @return
 */
static ILNamespace* class_loader_ilload_ast_to_namespace(AST* a);

/**
 * 名前空間の内側に定義される要素を IL に変換します.
 * @param self
 * @param current
 * @param parent
 * @param Namespacebody
 */
static void class_loader_ilload_Namespacebody(class_loader* self, ILNamespace* current, Vector* parent, AST* aNamespacebody);

/**
 * クラス宣言を IL に変換します.
 * @param self
 * @param current
 * @param class_decl
 */
static void class_loader_ilload_abstract_class(class_loader* self, ILNamespace* current, AST* aclass_decl);
static void class_loader_ilload_class(class_loader* self, ILNamespace* current, AST* aclass_decl);
static il_class* class_loader_ilload_classImpl(class_loader* self, ILNamespace* current, AST* aclass_decl);
static void class_loader_ilload_interface(class_loader* self, ILNamespace* current, AST* ainterface_decl);
static void class_loader_ilload_enum(class_loader* self, ILNamespace* current, AST* aenum_decl);

/**
 * 識別子を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
static void class_loader_ilload_identifier_list(class_loader* self, Vector* list, AST* asource);

//static il_factor* CLILFactorImpl(class_loader* self, AST* source);
//static il_stmt* class_loader_ilload_bodyImpl(class_loader* self, AST* source);

void ILLoadClassLoader(class_loader* self, AST* source_code) {
	assert(self->il_code == NULL);
	self->il_code = NewILToplevel();
	for (int i = 0; i < source_code->Children->Length; i++) {
		AST* child = AtAST(self->source_code, i);
		//import a
		if (child->Tag == AST_IMPORT_DECL_T || child->Tag == AST_IMPORT_DECL_LIST_T) {
			class_loader_ilload_import_list(self, child);
		//namespace Foo { ... }
		} else if (child->Tag == AST_NAMESPACE_DECL_T) {
			class_loader_ilload_namespace(self, self->il_code->Namespacelist, child);
		//print();
		} else if (IsStmtAST(child)) {
			CLILBody(self, self->il_code->statement_list, child);
		//def f() { ... }
		} else if(child->Tag == AST_FUNCTION_DECL_T) {
			class_loader_ilload_function(self, child);
		} else {
			fprintf(stderr, "ast is not collected\n");
			abort();
		}
	}
}

//private
static void class_loader_ilload_function(class_loader * self, AST* asource) {
	assert(asource->Tag == AST_FUNCTION_DECL_T);
	AST* afunc_name = AtAST(asource, 0);
	AST* atypeparams = AtAST(asource, 1);
	AST* aparam_list = AtAST(asource, 2);
	AST* afunc_body = AtAST(asource, 3);
	AST* aret_name = AtAST(asource, 4);
	ILFunction* ilfunc = NewILFunction(afunc_name->Attr.StringVValue);
	CLILTypeParameter(self, atypeparams, ilfunc->TypeParameters);
	CLILParameterList(self, ilfunc->Parameters, aparam_list);
	CLILBody(self, ilfunc->Statements, afunc_body);
	CLILGenericCache(aret_name, ilfunc->ReturnGCache);
	PushVector(self->il_code->function_list, ilfunc);
}

static void class_loader_ilload_import_list(class_loader* self, AST* asource) {
	if(asource->Tag == AST_IMPORT_DECL_LIST_T) {
		for(int i=0; i<asource->Children->Length; i++) {
			class_loader_ilload_import_list(self, AtAST(asource, i));
		}
	} else {
		assert(asource->Tag == AST_IMPORT_DECL_T);
		class_loader_ilload_import(self, asource);
	}
}

static void class_loader_ilload_import(class_loader* self, AST* aimport_decl) {
	assert(aimport_decl->Tag == AST_IMPORT_DECL_T);
	AST* apath = FirstAST(aimport_decl);
	ILImport* ret = NewILImport(apath->Attr.StringVValue);
	PushVector(self->il_code->import_list, ret);
}

static void class_loader_ilload_namespace(class_loader* self, Vector* parent, AST* aNamespacedecl) {
	assert(aNamespacedecl->Tag == AST_NAMESPACE_DECL_T);
	AST* aNamespacepath = FirstAST(aNamespacedecl);
	AST* aNamespacebody = SecondAST(aNamespacedecl);
	ILNamespace* iln = class_loader_ilload_ast_to_namespace(aNamespacepath);
	ILNamespace* top = GetRootILNamespace(iln);
	PushVector(parent, top);
	class_loader_ilload_Namespacepath_recursive(self, aNamespacepath, aNamespacebody);
	class_loader_ilload_Namespacebody(self, iln, iln->Namespacelist, aNamespacebody);
}

static void class_loader_ilload_Namespacepath_recursive(class_loader* self, AST* aNamespacepath, AST* aNamespacebody) {
	assert(aNamespacepath->Tag == AST_NAMESPACE_PATH_T ||
		   aNamespacepath->Tag == AST_NAMESPACE_PATH_LIST_T);
	if (aNamespacepath->Tag == AST_NAMESPACE_PATH_T) {
	} else if (aNamespacepath->Tag == AST_NAMESPACE_PATH_LIST_T) {
		for (int i = 0; i < aNamespacepath->Children->Length; i++) {
			class_loader_ilload_Namespacepath_recursive(self, AtAST(aNamespacepath, i), aNamespacebody);
		}
	}
}

static ILNamespace* class_loader_ilload_ast_to_namespace(AST* a) {
	assert(a->Tag == AST_NAMESPACE_PATH_T ||
	       a->Tag == AST_NAMESPACE_PATH_LIST_T);
	if(a->Tag == AST_NAMESPACE_PATH_T) {
		ILNamespace* ret = NewILNamespace(a->Attr.StringVValue);
		return ret;
	} else if(a->Tag == AST_NAMESPACE_PATH_LIST_T) {
		AST* al = FirstAST(a);
		AST* ar = SecondAST(a);
		ILNamespace* parent = class_loader_ilload_ast_to_namespace(al);
		ILNamespace* child = class_loader_ilload_ast_to_namespace(ar);
		child->parent = parent;
		PushVector(parent->Namespacelist, child);
		return child;
	}
	return NULL;
}

static void class_loader_ilload_Namespacebody(class_loader* self, ILNamespace* current, Vector* parent, AST* aNamespacebody) {
	if (IsBlankAST(aNamespacebody)) {
		return;
	}
	//namespace xxx { ...
	//namespace xxx { namespace yyy { ...
	if (aNamespacebody->Tag == AST_NAMESPACE_DECL_T) {
		class_loader_ilload_namespace(self, parent, aNamespacebody);
		//namespace xxx { abstract class yyy { ...
	} else if(aNamespacebody->Tag == AST_ABSTRACT_CLASS_DECL_T) {
		class_loader_ilload_abstract_class(self, current, aNamespacebody);
		//namespace xxx { class yyy { ...
	} else if (aNamespacebody->Tag == AST_CLASS_DECL_T) {
		class_loader_ilload_class(self, current, aNamespacebody);
		//namespace xxx { interface yyy { ...
	} else if (aNamespacebody->Tag == AST_INTERFACE_DECL) {
		class_loader_ilload_interface(self, current, aNamespacebody);
		//namespace xxx { enum yyy { ...
	} else if(aNamespacebody->Tag == AST_ENUM_DECL_T) {
		class_loader_ilload_enum(self, current, aNamespacebody);
		//namespace xxx { any yyy { ...
	} else if (aNamespacebody->Tag == AST_NAMESPACE_MEMBER_DECL_LIST_T) {
		for (int i = 0; i < aNamespacebody->Children->Length; i++) {
			AST* amember = AtAST(aNamespacebody, i);
			class_loader_ilload_Namespacebody(self, current, parent, amember);
		}
	}
}

static void class_loader_ilload_abstract_class(class_loader* self, ILNamespace* current, AST* aclass_decl) {
	assert(aclass_decl->Tag == AST_ABSTRACT_CLASS_DECL_T);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = true;
}

static void class_loader_ilload_class(class_loader* self, ILNamespace* current, AST* aclass_decl) {
	assert(aclass_decl->Tag == AST_CLASS_DECL_T);
	il_class* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->is_abstract = false;
}

static il_class* class_loader_ilload_classImpl(class_loader* self, ILNamespace* current, AST* aclass_decl) {
	AST* atypename = FirstAST(aclass_decl);
	AST* aextend_list = SecondAST(aclass_decl);
	AST* amember_tree = AtAST(aclass_decl, 2);
	il_class* ilclassz = NewILClass(atypename->Attr.StringVValue);
	il_type* iltype = WrapILClass(ilclassz);
	//class Foo<A, B>
	CLILTypeParameter(self, FirstAST(atypename), ilclassz->GetParameterListType);
	//class Foo : X, Y 
	CLILTypenameList(self, ilclassz->extend_list, aextend_list);
	//public:
	//    ....
	//    ....
	if (!IsBlankAST(amember_tree)) {
		CLILMemberTree(self, iltype, amember_tree);
	}
	PushVector(current->type_list, iltype);
	return ilclassz;
}

static void class_loader_ilload_interface(class_loader* self, ILNamespace* current, AST* ainterface_decl) {
	AST* atypename = FirstAST(ainterface_decl);
	AST* aextends_list = SecondAST(ainterface_decl);
	AST* amember_tree = AtAST(ainterface_decl, 2);
	il_interface* ilinter = NewILInterface(atypename->Attr.StringVValue);
	il_type* iltype = WrapILInterface(ilinter);
	//interface Foo<A, B>
	CLILTypeParameter(self, FirstAST(atypename), ilinter->GetParameterListType);
	//interface Foo : XXX, YYY, CCC
	CLILTypenameList(self, ilinter->extends_list, aextends_list);
	//public:
	//    ...
	if (!IsBlankAST(amember_tree)) {
		CLILMemberTree(self, iltype, amember_tree);
	}
	PushVector(current->type_list, iltype);
}

static void class_loader_ilload_enum(class_loader * self, ILNamespace * current, AST* aenum_decl) {
	assert(aenum_decl->Tag == AST_ENUM_DECL_T);
	AST* aname_list = FirstAST(aenum_decl);
	il_enum* ilenum = NewILEnum(aenum_decl->Attr.StringVValue);
	class_loader_ilload_identifier_list(self, ilenum->item_vec, aname_list);
	PushVector(current->type_list, WrapILEnum(ilenum));
}

static void class_loader_ilload_identifier_list(class_loader * self, Vector * list, AST* asource) {
	if (asource->Tag == AST_IDENTIFIER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			class_loader_ilload_identifier_list(self, list, AtAST(asource, i));
		}
	} else if(asource->Tag == AST_IDENTIFIER_T) {
		StringView str = asource->Attr.StringVValue;
		PushVector(list, str);
	}
}
