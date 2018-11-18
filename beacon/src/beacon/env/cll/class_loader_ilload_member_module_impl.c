#include "class_loader_ilload_member_module_impl.h"
#include "../../il/il_TYPE_IMPL.h"
#include "../../il/il_field.h"
#include "../../il/il_method.h"
#include "../../il/il_constructor.h"
#include "../../il/il_constructor_chain.h"
#include "../../il/il_operator_overload.h"
#include "../../il/il_property.h"
#include "../../error.h"
#include "class_loader_ilload_type_module_impl.h"
#include "class_loader_ilload_factor_module_impl.h"
#include "class_loader_ilload_stmt_module_impl.h"
#include <assert.h>

static ILPropertyBody* CLILProperty_body(ClassLoader* self, ILType* current, AST* abody, ILPropertyBodyTag tag, AccessLevel level);

void CLILMemberTree(ClassLoader* self, ILType* current, AST* atree) {
	if (atree->Tag == AST_ACCESS_MEMBER_TREE_T) {
		for (int i = 0; i < atree->Children->Length; i++) {
			CLILMemberTree(self, current, AtAST(atree, i));
		}
	} else if (atree->Tag == AST_ACCESS_MEMBER_LIST_T) {
		AST* aaccess = FirstAST(atree);
		AST* amember_list = SecondAST(atree);
		AccessLevel level = ASTCastToAccess(aaccess);
		CLILMemberList(self, current, amember_list, level);
	}
}

void CLILMemberList(ClassLoader* self, ILType* current, AST* amember, AccessLevel level) {
	if(amember->Tag == AST_MEMBER_DECL_LIST_T) {
		for(int i=0; i<amember->Children->Length; i++) {
			CLILMemberList(self, current, AtAST(amember, i), level);
		}
	} else if(amember->Tag == AST_MEMBER_DECL_T) {
		AST* achild = FirstAST(amember);
		if (achild->Tag == AST_FIELD_DECL_T) {
			CLILField(self, current, achild, level);
		} else if(achild->Tag == AST_PROP_DECL_T) {
			CLILProperty(self, current, achild, level);
		} else if (achild->Tag == AST_METHOD_DECL_T) {
			CLILMethod(self, current, achild, level);
		} else if (achild->Tag == AST_CONSTRUCTOR_DECL_T) {
			CLILConstructor(self, current, achild, level);
		} else if(achild->Tag == AST_OPERATOR_OVERLOAD_T) {
			CLILOperatorOverload(self, current, achild, level);
		}
	}
}

void CLILField(ClassLoader* self, ILType* current, AST* afield, AccessLevel level) {
	//assert(current->Tag == ILTYPE_CLASS_T);
	AST* amodifier = FirstAST(afield);
	AST* aGetTypeName = SecondAST(afield);
	AST* aaccess_name = AtAST(afield, 2);
	AST* afact = AtAST(afield, 3);
	//インターフェイスはフィールドを持てない
	if(current->Tag == ILTYPE_INTERFACE_T) {
		bc_Panic(
			BCERROR_INTERFACE_HAS_FIELD_T,
			Ref2Str(current->Kind.Interface->Name),
			Ref2Str(aaccess_name->Attr.StringVValue)
		);
		return;
	}
	ILField* v = NewILField(aaccess_name->Attr.StringVValue);
	CLILGenericCache(aGetTypeName, v->GCache);
	bool error;
	v->Access = level;
	v->Modifier = ASTCastToModifier(amodifier, &error);
	AddFieldILType(current, v);
	//設定されているなら初期値も
	if(!IsBlankAST(afact)) {
		v->InitialValue = CLILFactor(self, afact);
	}
	//重複する修飾子を検出
	if(error) {
		bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->Name));
	}
}

void CLILProperty(ClassLoader* self, ILType* current, AST* aprop, AccessLevel level) {
	AST* amod = AtAST(aprop, 0);
	AST* atypename = AtAST(aprop, 1);
	AST* aset = AtAST(aprop, 2);
	AST* aget = AtAST(aprop, 3);
	StringView propname = aprop->Attr.StringVValue;
	ILProperty* ret = ILNewProperty(propname);
	CLILGenericCache(atypename, ret->GCache);
	if(IsBlankAST(amod)) {
		ret->Modifier = MODIFIER_NONE_T;
	} else {
		bool err = false;
		ret->Modifier = ASTCastToModifier(amod, &err);
		if(err) {
			bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(ret->Name));
		}
	}
	ret->Access = level;
	ret->Set = CLILProperty_body(self, current, aset, IL_PROPERTY_SET_T, level);
	ret->Get = CLILProperty_body(self, current, aget, IL_PROPERTY_GET_T, level);
	AddPropertyILType(current, ret);
	if(ret->Set->IsShort != ret->Get->IsShort) {
		bc_Panic(BCERROR_INVALID_PROPERTY_DECL_T, Ref2Str(current->Kind.Class->Name), Ref2Str(propname));
	}
}

void CLILMethod(ClassLoader* self, ILType* current, AST* amethod, AccessLevel level) {
	assert(current->Tag == ILTYPE_CLASS_T || current->Tag == ILTYPE_INTERFACE_T);
	AST* amodifier = AtAST(amethod, 0);
	AST* afunc_name = AtAST(amethod, 1);
	AST* ageneric = AtAST(amethod, 2);
	AST* aparam_list = AtAST(amethod, 3);
	AST* afunc_body = AtAST(amethod, 4);
	AST* aret_name = AtAST(amethod, 5);
	ILMethod* v = NewILMethod(afunc_name->Attr.StringVValue);
	CLILTypeParameter(self, ageneric, v->TypeParameters);
	CLILGenericCache(aret_name, v->ReturnGCache);
	bool error;
	v->Access = level;
	v->Modifier = ASTCastToModifier(amodifier, &error);
	CLILParameterList(self, v->Parameters, aparam_list);
	CLILBody(self, v->Statements, afunc_body);
	//メソッドの本文が省略されているかどうか
	//例えばネイティブメソッドや抽象メソッドは省略されているべき
	if(IsBlankAST(afunc_body)) {
		v->IsNoStmt = true;
	}
	AddMethodILType(current, v);
	//重複する修飾子を検出
	if(error) {
		bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->Name));
	}
}

void CLILConstructor(ClassLoader* self, ILType* current, AST* aconstructor, AccessLevel level) {
	//assert(current->Tag == ILTYPE_CLASS_T);
	AST* aparams = AtAST(aconstructor, 0);
	AST* achain = AtAST(aconstructor, 1);
	AST* abody = AtAST(aconstructor, 2);
	ILConstructorChain* ilchain = NULL;
	//インターフェイスはコンストラクタを持てない
	if(current->Tag == ILTYPE_INTERFACE_T) {
		bc_Panic(
			BCERROR_INTERFACE_HAS_CTOR_T,
			Ref2Str(current->Kind.Interface->Name)
		);
		return;
	}
	if (!IsBlankAST(achain)) {
		AST* achain_type = FirstAST(achain);
		AST* aargs = SecondAST(achain);
		ilchain = NewILConstructorChain();
		ilchain->Type = ASTCastToChainType(achain_type);
		CLILArgumentList(self, ilchain->Arguments, aargs);
	}
	ILConstructor* ilcons = NewILConstructor();
	ilcons->Access = level;
	ilcons->Chain = ilchain;
	CLILParameterList(self, ilcons->Parameters, aparams);
	CLILBody(self, ilcons->Statements, abody);
	PushVector(current->Kind.Class->Constructors, ilcons);
}

void CLILOperatorOverload(ClassLoader* self, ILType* current, AST* aopov, AccessLevel level) {
	//assert(aopov->Tag == AST_OPERATOR_OVERLOAD_T);
	OperatorType ot = aopov->Attr.OperatorValue;
	AST* aparam_list = AtAST(aopov, 0);
	AST* abody = AtAST(aopov, 1);
	AST* areturn = AtAST(aopov, 2);
	//インターフェイスはコンストラクタを持てない
	if(current->Tag == ILTYPE_INTERFACE_T) {
		bc_Panic(
			BCERROR_INTERFACE_HAS_OPOV_T,
			Ref2Str(current->Kind.Interface->Name),
			OperatorToString(ot)
		);
		return;
	}
	ILOperatorOverload* ilopov = NewILOperatorOverload(ot);
	ilopov->Access = level;
	CLILParameterList(self, ilopov->Parameters, aparam_list);
	CLILBody(self, ilopov->Statements, abody);
	CLILGenericCache(areturn, ilopov->ReturnGCache);
	PushVector(current->Kind.Class->OperatorOverloads, ilopov);
}
//private
static ILPropertyBody* CLILProperty_body(ClassLoader* self, ILType* current, AST* abody, ILPropertyBodyTag tag, AccessLevel level) {
	ILPropertyBody* ret = ILNewPropertyBody(tag);
	assert(abody->Tag == AST_PROP_SET_T || abody->Tag == AST_PROP_GET_T);
	AST* aacess = FirstAST(abody);
	AST* astmt_list = SecondAST(abody);
	ret->Access = level;
	CLILBody(self, ret->Statements, astmt_list);
	if(!IsBlankAST(aacess)) {
		ret->Access = aacess->Attr.AccessValue;
	}
	if(ret->Statements->Length == 0) {
		ret->IsShort = true;
	}
	return ret;
}