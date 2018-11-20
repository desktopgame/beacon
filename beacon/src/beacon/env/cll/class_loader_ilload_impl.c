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
static void class_loader_ilload_function(bc_ClassLoader* self, bc_AST* asource);

/**
 * インポートの一覧を IL に変換します.
 * @param self
 * @param source
 */
static void class_loader_ilload_import_list(bc_ClassLoader* self, bc_AST* asource);

/**
 * インポート宣言を IL に変換します.
 * @param self
 * @param import_decl
 */
static void class_loader_ilload_import(bc_ClassLoader* self, bc_AST* aimport_decl);

/**
 * 名前空間とその内側のエントリ全てを IL に変換します.
 * @param self
 * @param parent
 * @param Namespacedecl
 */
static void class_loader_ilload_namespace(bc_ClassLoader* self, bc_Vector* parent, bc_AST* aNamespacedecl);

/**
 * 名前空間のパス(A.B.C)を解析します.
 * デバッグ用の関数で、今は特に何も行いません。
 * @param self
 * @param Namespacepath
 * @param Namespacebody
 */
static void class_loader_ilload_Namespacepath_recursive(bc_ClassLoader* self, bc_AST* aNamespacepath, bc_AST* Namespacebody);

/**
 * 名前空間(またはそのリスト)を IL に変換します.
 * @param a
 * @return
 */
static ILNamespace* class_loader_ilload_ast_to_namespace(bc_AST* a);

/**
 * 名前空間の内側に定義される要素を IL に変換します.
 * @param self
 * @param current
 * @param parent
 * @param Namespacebody
 */
static void class_loader_ilload_Namespacebody(bc_ClassLoader* self, ILNamespace* current, bc_Vector* parent, bc_AST* aNamespacebody);

/**
 * クラス宣言を IL に変換します.
 * @param self
 * @param current
 * @param class_decl
 */
static void class_loader_ilload_abstract_class(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl);
static void class_loader_ilload_class(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl);
static ILClass* class_loader_ilload_classImpl(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl);
static void class_loader_ilload_interface(bc_ClassLoader* self, ILNamespace* current, bc_AST* ainterface_decl);
static void class_loader_ilload_enum(bc_ClassLoader* self, ILNamespace* current, bc_AST* aenum_decl);

/**
 * 識別子を IL に変換します.
 * @param self
 * @param list
 * @param source
 */
static void class_loader_ilload_identifier_list(bc_ClassLoader* self, bc_Vector* list, bc_AST* asource);

//static ILFactor* CLILFactorImpl(ClassLoader* self, AST* source);
//static ILStatement* class_loader_ilload_bodyImpl(ClassLoader* self, AST* source);

void ILLoadClassLoader(bc_ClassLoader* self, bc_AST* source_code) {
	assert(self->ILCode == NULL);
	self->ILCode = NewILToplevel();
	for (int i = 0; i < source_code->Children->Length; i++) {
		bc_AST* child = bc_AtAST(self->SourceCode, i);
		//import a
		if (child->Tag == AST_IMPORT_DECL_T || child->Tag == AST_IMPORT_DECL_LIST_T) {
			class_loader_ilload_import_list(self, child);
		//namespace Foo { ... }
		} else if (child->Tag == AST_NAMESPACE_DECL_T) {
			class_loader_ilload_namespace(self, self->ILCode->NamespaceList, child);
		//print();
		} else if (bc_IsStmtAST(child)) {
			CLILBody(self, self->ILCode->StatementList, child);
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
static void class_loader_ilload_function(bc_ClassLoader * self, bc_AST* asource) {
	assert(asource->Tag == AST_FUNCTION_DECL_T);
	bc_AST* afunc_name = bc_AtAST(asource, 0);
	bc_AST* atypeparams = bc_AtAST(asource, 1);
	bc_AST* aparam_list = bc_AtAST(asource, 2);
	bc_AST* afunc_body = bc_AtAST(asource, 3);
	bc_AST* aret_name = bc_AtAST(asource, 4);
	ILFunction* ilfunc = NewILFunction(afunc_name->Attr.StringVValue);
	CLILTypeParameter(self, atypeparams, ilfunc->TypeParameters);
	CLILParameterList(self, ilfunc->Parameters, aparam_list);
	CLILBody(self, ilfunc->Statements, afunc_body);
	CLILGenericCache(aret_name, ilfunc->ReturnGCache);
	bc_PushVector(self->ILCode->FunctionList, ilfunc);
}

static void class_loader_ilload_import_list(bc_ClassLoader* self, bc_AST* asource) {
	if(asource->Tag == AST_IMPORT_DECL_LIST_T) {
		for(int i=0; i<asource->Children->Length; i++) {
			class_loader_ilload_import_list(self, bc_AtAST(asource, i));
		}
	} else {
		assert(asource->Tag == AST_IMPORT_DECL_T);
		class_loader_ilload_import(self, asource);
	}
}

static void class_loader_ilload_import(bc_ClassLoader* self, bc_AST* aimport_decl) {
	assert(aimport_decl->Tag == AST_IMPORT_DECL_T);
	bc_AST* apath = bc_FirstAST(aimport_decl);
	ILImport* ret = NewILImport(apath->Attr.StringVValue);
	bc_PushVector(self->ILCode->ImportList, ret);
}

static void class_loader_ilload_namespace(bc_ClassLoader* self, bc_Vector* parent, bc_AST* aNamespacedecl) {
	assert(aNamespacedecl->Tag == AST_NAMESPACE_DECL_T);
	bc_AST* aNamespacepath = bc_FirstAST(aNamespacedecl);
	bc_AST* aNamespacebody = bc_SecondAST(aNamespacedecl);
	ILNamespace* iln = class_loader_ilload_ast_to_namespace(aNamespacepath);
	ILNamespace* top = GetRootILNamespace(iln);
	bc_PushVector(parent, top);
	class_loader_ilload_Namespacepath_recursive(self, aNamespacepath, aNamespacebody);
	class_loader_ilload_Namespacebody(self, iln, iln->NamespaceList, aNamespacebody);
}

static void class_loader_ilload_Namespacepath_recursive(bc_ClassLoader* self, bc_AST* aNamespacepath, bc_AST* aNamespacebody) {
	assert(aNamespacepath->Tag == AST_NAMESPACE_PATH_T ||
		   aNamespacepath->Tag == AST_NAMESPACE_PATH_LIST_T);
	if (aNamespacepath->Tag == AST_NAMESPACE_PATH_T) {
	} else if (aNamespacepath->Tag == AST_NAMESPACE_PATH_LIST_T) {
		for (int i = 0; i < aNamespacepath->Children->Length; i++) {
			class_loader_ilload_Namespacepath_recursive(self, bc_AtAST(aNamespacepath, i), aNamespacebody);
		}
	}
}

static ILNamespace* class_loader_ilload_ast_to_namespace(bc_AST* a) {
	assert(a->Tag == AST_NAMESPACE_PATH_T ||
	       a->Tag == AST_NAMESPACE_PATH_LIST_T);
	if(a->Tag == AST_NAMESPACE_PATH_T) {
		ILNamespace* ret = NewILNamespace(a->Attr.StringVValue);
		return ret;
	} else if(a->Tag == AST_NAMESPACE_PATH_LIST_T) {
		bc_AST* al = bc_FirstAST(a);
		bc_AST* ar = bc_SecondAST(a);
		ILNamespace* parent = class_loader_ilload_ast_to_namespace(al);
		ILNamespace* child = class_loader_ilload_ast_to_namespace(ar);
		child->Parent = parent;
		bc_PushVector(parent->NamespaceList, child);
		return child;
	}
	return NULL;
}

static void class_loader_ilload_Namespacebody(bc_ClassLoader* self, ILNamespace* current, bc_Vector* parent, bc_AST* aNamespacebody) {
	if (bc_IsBlankAST(aNamespacebody)) {
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
			bc_AST* amember = bc_AtAST(aNamespacebody, i);
			class_loader_ilload_Namespacebody(self, current, parent, amember);
		}
	}
}

static void class_loader_ilload_abstract_class(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl) {
	assert(aclass_decl->Tag == AST_ABSTRACT_CLASS_DECL_T);
	ILClass* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->IsAbstract = true;
}

static void class_loader_ilload_class(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl) {
	assert(aclass_decl->Tag == AST_CLASS_DECL_T);
	ILClass* ilc = class_loader_ilload_classImpl(self, current, aclass_decl);
	ilc->IsAbstract = false;
}

static ILClass* class_loader_ilload_classImpl(bc_ClassLoader* self, ILNamespace* current, bc_AST* aclass_decl) {
	bc_AST* atypename = bc_FirstAST(aclass_decl);
	bc_AST* aextend_list = bc_SecondAST(aclass_decl);
	bc_AST* amember_tree = bc_AtAST(aclass_decl, 2);
	ILClass* ilclassz = NewILClass(atypename->Attr.StringVValue);
	ILType* iltype = WrapILClass(ilclassz);
	//class Foo<A, B>
	CLILTypeParameter(self, bc_FirstAST(atypename), ilclassz->TypeParameters);
	//class Foo : X, Y 
	CLILTypenameList(self, ilclassz->Extends, aextend_list);
	//public:
	//    ....
	//    ....
	if (!bc_IsBlankAST(amember_tree)) {
		CLILMemberTree(self, iltype, amember_tree);
	}
	bc_PushVector(current->TypeList, iltype);
	return ilclassz;
}

static void class_loader_ilload_interface(bc_ClassLoader* self, ILNamespace* current, bc_AST* ainterface_decl) {
	bc_AST* atypename = bc_FirstAST(ainterface_decl);
	bc_AST* aextends_list = bc_SecondAST(ainterface_decl);
	bc_AST* amember_tree = bc_AtAST(ainterface_decl, 2);
	ILInterface* ilinter = NewILInterface(atypename->Attr.StringVValue);
	ILType* iltype = WrapILInterface(ilinter);
	//interface Foo<A, B>
	CLILTypeParameter(self, bc_FirstAST(atypename), ilinter->TypeParameters);
	//interface Foo : XXX, YYY, CCC
	CLILTypenameList(self, ilinter->Extends, aextends_list);
	//public:
	//    ...
	if (!bc_IsBlankAST(amember_tree)) {
		CLILMemberTree(self, iltype, amember_tree);
	}
	bc_PushVector(current->TypeList, iltype);
}

static void class_loader_ilload_enum(bc_ClassLoader * self, ILNamespace * current, bc_AST* aenum_decl) {
	assert(aenum_decl->Tag == AST_ENUM_DECL_T);
	bc_AST* aname_list = bc_FirstAST(aenum_decl);
	ILEnum* ilenum = NewILEnum(aenum_decl->Attr.StringVValue);
	class_loader_ilload_identifier_list(self, ilenum->Items, aname_list);
	bc_PushVector(current->TypeList, WrapILEnum(ilenum));
}

static void class_loader_ilload_identifier_list(bc_ClassLoader * self, bc_Vector * list, bc_AST* asource) {
	if (asource->Tag == AST_IDENTIFIER_LIST_T) {
		for (int i = 0; i < asource->Children->Length; i++) {
			class_loader_ilload_identifier_list(self, list, bc_AtAST(asource, i));
		}
	} else if(asource->Tag == AST_IDENTIFIER_T) {
		bc_StringView str = asource->Attr.StringVValue;
		bc_PushVector(list, str);
	}
}
