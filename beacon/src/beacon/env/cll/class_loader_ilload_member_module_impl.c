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

static ILPropertyBody* CLILProperty_body(ClassLoader* self, ILType* current, bc_AST* abody, ILPropertyBodyTag tag, bc_AccessLevel level);

void CLILMemberTree(ClassLoader* self, ILType* current, bc_AST* atree) {
	if (atree->Tag == AST_ACCESS_MEMBER_TREE_T) {
		for (int i = 0; i < atree->Children->Length; i++) {
			CLILMemberTree(self, current, bc_AtAST(atree, i));
		}
	} else if (atree->Tag == AST_ACCESS_MEMBER_LIST_T) {
		bc_AST* aaccess = bc_FirstAST(atree);
		bc_AST* amember_list = bc_SecondAST(atree);
		bc_AccessLevel level = bc_ASTCastToAccess(aaccess);
		CLILMemberList(self, current, amember_list, level);
	}
}

void CLILMemberList(ClassLoader* self, ILType* current, bc_AST* amember, bc_AccessLevel level) {
	if(amember->Tag == AST_MEMBER_DECL_LIST_T) {
		for(int i=0; i<amember->Children->Length; i++) {
			CLILMemberList(self, current, bc_AtAST(amember, i), level);
		}
	} else if(amember->Tag == AST_MEMBER_DECL_T) {
		bc_AST* achild = bc_FirstAST(amember);
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

void CLILField(ClassLoader* self, ILType* current, bc_AST* afield, bc_AccessLevel level) {
	//assert(current->Tag == ILTYPE_CLASS_T);
	bc_AST* amodifier = bc_FirstAST(afield);
	bc_AST* aGetTypeName = bc_SecondAST(afield);
	bc_AST* aaccess_name = bc_AtAST(afield, 2);
	bc_AST* afact = bc_AtAST(afield, 3);
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
	v->Modifier = bc_ASTCastToModifier(amodifier, &error);
	AddFieldILType(current, v);
	//設定されているなら初期値も
	if(!bc_IsBlankAST(afact)) {
		v->InitialValue = CLILFactor(self, afact);
	}
	//重複する修飾子を検出
	if(error) {
		bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->Name));
	}
}

void CLILProperty(ClassLoader* self, ILType* current, bc_AST* aprop, bc_AccessLevel level) {
	bc_AST* amod = bc_AtAST(aprop, 0);
	bc_AST* atypename = bc_AtAST(aprop, 1);
	bc_AST* aset = bc_AtAST(aprop, 2);
	bc_AST* aget = bc_AtAST(aprop, 3);
	StringView propname = aprop->Attr.StringVValue;
	ILProperty* ret = ILNewProperty(propname);
	CLILGenericCache(atypename, ret->GCache);
	if(bc_IsBlankAST(amod)) {
		ret->Modifier = MODIFIER_NONE_T;
	} else {
		bool err = false;
		ret->Modifier = bc_ASTCastToModifier(amod, &err);
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

void CLILMethod(ClassLoader* self, ILType* current, bc_AST* amethod, bc_AccessLevel level) {
	assert(current->Tag == ILTYPE_CLASS_T || current->Tag == ILTYPE_INTERFACE_T);
	bc_AST* amodifier = bc_AtAST(amethod, 0);
	bc_AST* afunc_name = bc_AtAST(amethod, 1);
	bc_AST* ageneric = bc_AtAST(amethod, 2);
	bc_AST* aparam_list = bc_AtAST(amethod, 3);
	bc_AST* afunc_body = bc_AtAST(amethod, 4);
	bc_AST* aret_name = bc_AtAST(amethod, 5);
	ILMethod* v = NewILMethod(afunc_name->Attr.StringVValue);
	CLILTypeParameter(self, ageneric, v->TypeParameters);
	CLILGenericCache(aret_name, v->ReturnGCache);
	bool error;
	v->Access = level;
	v->Modifier = bc_ASTCastToModifier(amodifier, &error);
	CLILParameterList(self, v->Parameters, aparam_list);
	CLILBody(self, v->Statements, afunc_body);
	//メソッドの本文が省略されているかどうか
	//例えばネイティブメソッドや抽象メソッドは省略されているべき
	if(bc_IsBlankAST(afunc_body)) {
		v->IsNoStmt = true;
	}
	AddMethodILType(current, v);
	//重複する修飾子を検出
	if(error) {
		bc_Panic(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->Name));
	}
}

void CLILConstructor(ClassLoader* self, ILType* current, bc_AST* aconstructor, bc_AccessLevel level) {
	//assert(current->Tag == ILTYPE_CLASS_T);
	bc_AST* aparams = bc_AtAST(aconstructor, 0);
	bc_AST* achain = bc_AtAST(aconstructor, 1);
	bc_AST* abody = bc_AtAST(aconstructor, 2);
	ILConstructorChain* ilchain = NULL;
	//インターフェイスはコンストラクタを持てない
	if(current->Tag == ILTYPE_INTERFACE_T) {
		bc_Panic(
			BCERROR_INTERFACE_HAS_CTOR_T,
			Ref2Str(current->Kind.Interface->Name)
		);
		return;
	}
	if (!bc_IsBlankAST(achain)) {
		bc_AST* achain_type = bc_FirstAST(achain);
		bc_AST* aargs = bc_SecondAST(achain);
		ilchain = NewILConstructorChain();
		ilchain->Type = bc_ASTCastToChainType(achain_type);
		CLILArgumentList(self, ilchain->Arguments, aargs);
	}
	ILConstructor* ilcons = NewILConstructor();
	ilcons->Access = level;
	ilcons->Chain = ilchain;
	CLILParameterList(self, ilcons->Parameters, aparams);
	CLILBody(self, ilcons->Statements, abody);
	PushVector(current->Kind.Class->Constructors, ilcons);
}

void CLILOperatorOverload(ClassLoader* self, ILType* current, bc_AST* aopov, bc_AccessLevel level) {
	//assert(aopov->Tag == AST_OPERATOR_OVERLOAD_T);
	bc_OperatorType ot = aopov->Attr.OperatorValue;
	bc_AST* aparam_list = bc_AtAST(aopov, 0);
	bc_AST* abody = bc_AtAST(aopov, 1);
	bc_AST* areturn = bc_AtAST(aopov, 2);
	//インターフェイスはコンストラクタを持てない
	if(current->Tag == ILTYPE_INTERFACE_T) {
		bc_Panic(
			BCERROR_INTERFACE_HAS_OPOV_T,
			Ref2Str(current->Kind.Interface->Name),
			bc_OperatorToString(ot)
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
static ILPropertyBody* CLILProperty_body(ClassLoader* self, ILType* current, bc_AST* abody, ILPropertyBodyTag tag, bc_AccessLevel level) {
	ILPropertyBody* ret = ILNewPropertyBody(tag);
	assert(abody->Tag == AST_PROP_SET_T || abody->Tag == AST_PROP_GET_T);
	bc_AST* aacess = bc_FirstAST(abody);
	bc_AST* astmt_list = bc_SecondAST(abody);
	ret->Access = level;
	CLILBody(self, ret->Statements, astmt_list);
	if(!bc_IsBlankAST(aacess)) {
		ret->Access = aacess->Attr.AccessValue;
	}
	if(ret->Statements->Length == 0) {
		ret->IsShort = true;
	}
	return ret;
}