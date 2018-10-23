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

static il_property_body* CLILProperty_body(class_loader* self, il_type* current, AST* abody, il_property_body_tag tag, AccessLevel level);

void CLILMemberTree(class_loader* self, il_type* current, AST* atree) {
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

void CLILMemberList(class_loader* self, il_type* current, AST* amember, AccessLevel level) {
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

void CLILField(class_loader* self, il_type* current, AST* afield, AccessLevel level) {
	//assert(current->Tag == ilTYPE_CLASS_T);
	AST* amodifier = FirstAST(afield);
	AST* aGetTypeName = SecondAST(afield);
	AST* aaccess_name = AtAST(afield, 2);
	AST* afact = AtAST(afield, 3);
	//インターフェイスはフィールドを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_FIELD_T,
			Ref2Str(current->u.interface_->namev),
			Ref2Str(aaccess_name->Attr.StringVValue)
		);
		return;
	}
	ILField* v = NewILField(aaccess_name->Attr.StringVValue);
	CLILGenericCache(aGetTypeName, v->fqcn);
	bool error;
	v->access = level;
	v->modifier = ASTCastToModifier(amodifier, &error);
	AddFieldILType(current, v);
	//設定されているなら初期値も
	if(!IsBlankAST(afact)) {
		v->initial_value = CLILFactor(self, afact);
	}
	//重複する修飾子を検出
	if(error) {
		ThrowBCError(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->namev));
	}
}

void CLILProperty(class_loader* self, il_type* current, AST* aprop, AccessLevel level) {
	AST* amod = AtAST(aprop, 0);
	AST* atypename = AtAST(aprop, 1);
	AST* aset = AtAST(aprop, 2);
	AST* aget = AtAST(aprop, 3);
	StringView propname = aprop->Attr.StringVValue;
	il_property* ret = il_property_new(propname);
	CLILGenericCache(atypename, ret->fqcn);
	if(IsBlankAST(amod)) {
		ret->modifier = MODIFIER_NONE_T;
	} else {
		bool err = false;
		ret->modifier = ASTCastToModifier(amod, &err);
		if(err) {
			ThrowBCError(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(ret->namev));
		}
	}
	ret->access = level;
	ret->set = CLILProperty_body(self, current, aset, ilPROPERTY_SET_T, level);
	ret->get = CLILProperty_body(self, current, aget, ilPROPERTY_GET_T, level);
	AddPropertyILType(current, ret);
	if(ret->set->is_short != ret->get->is_short) {
		ThrowBCError(BCERROR_INVALID_PROPERTY_DECL_T, Ref2Str(current->u.class_->namev), Ref2Str(propname));
	}
}

void CLILMethod(class_loader* self, il_type* current, AST* amethod, AccessLevel level) {
	assert(current->tag == ilTYPE_CLASS_T || current->tag == ilTYPE_INTERFACE_T);
	AST* amodifier = AtAST(amethod, 0);
	AST* afunc_name = AtAST(amethod, 1);
	AST* ageneric = AtAST(amethod, 2);
	AST* aparam_list = AtAST(amethod, 3);
	AST* afunc_body = AtAST(amethod, 4);
	AST* aret_name = AtAST(amethod, 5);
	il_method* v = NewILMethod(afunc_name->Attr.StringVValue);
	CLILTypeParameter(self, ageneric, v->GetParameterListType);
	CLILGenericCache(aret_name, v->return_fqcn);
	bool error;
	v->access = level;
	v->modifier = ASTCastToModifier(amodifier, &error);
	CLILParameterList(self, v->parameter_list, aparam_list);
	CLILBody(self, v->statement_list, afunc_body);
	//メソッドの本文が省略されているかどうか
	//例えばネイティブメソッドや抽象メソッドは省略されているべき
	if(IsBlankAST(afunc_body)) {
		v->no_stmt = true;
	}
	AddMethodILType(current, v);
	//重複する修飾子を検出
	if(error) {
		ThrowBCError(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->namev));
	}
}

void CLILConstructor(class_loader* self, il_type* current, AST* aconstructor, AccessLevel level) {
	//assert(current->Tag == ilTYPE_CLASS_T);
	AST* aparams = AtAST(aconstructor, 0);
	AST* achain = AtAST(aconstructor, 1);
	AST* abody = AtAST(aconstructor, 2);
	ILConstructorChain* ilchain = NULL;
	//インターフェイスはコンストラクタを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_CTOR_T,
			Ref2Str(current->u.interface_->namev)
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
	PushVector(current->u.class_->constructor_list, ilcons);
}

void CLILOperatorOverload(class_loader* self, il_type* current, AST* aopov, AccessLevel level) {
	//assert(aopov->Tag == AST_OPERATOR_OVERLOAD_T);
	OperatorType ot = aopov->Attr.OperatorValue;
	AST* aparam_list = AtAST(aopov, 0);
	AST* abody = AtAST(aopov, 1);
	AST* areturn = AtAST(aopov, 2);
	//インターフェイスはコンストラクタを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_OPOV_T,
			Ref2Str(current->u.interface_->namev),
			OperatorToString(ot)
		);
		return;
	}
	il_operator_overload* ilopov = NewILOperatorOverload(ot);
	ilopov->access = level;
	CLILParameterList(self, ilopov->parameter_list, aparam_list);
	CLILBody(self, ilopov->statement_list, abody);
	CLILGenericCache(areturn, ilopov->return_fqcn);
	PushVector(current->u.class_->operator_overload_list, ilopov);
}
//private
static il_property_body* CLILProperty_body(class_loader* self, il_type* current, AST* abody, il_property_body_tag tag, AccessLevel level) {
	il_property_body* ret = il_property_body_new(tag);
	assert(abody->Tag == AST_PROP_SET_T || abody->Tag == AST_PROP_GET_T);
	AST* aacess = FirstAST(abody);
	AST* astmt_list = SecondAST(abody);
	ret->access = level;
	CLILBody(self, ret->statement_list, astmt_list);
	if(!IsBlankAST(aacess)) {
		ret->access = aacess->Attr.AccessValue;
	}
	if(ret->statement_list->Length == 0) {
		ret->is_short = true;
	}
	return ret;
}