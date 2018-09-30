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

static il_property_body* CLIL_prop_body(class_loader* self, il_type* current, ast* abody, il_property_body_tag tag, access_level level);

void CLIL_member_tree(class_loader* self, il_type* current, ast* atree) {
	if (atree->tag == AST_ACCESS_MEMBER_TREE_T) {
		for (int i = 0; i < atree->vchildren->length; i++) {
			CLIL_member_tree(self, current, AtAST(atree, i));
		}
	} else if (atree->tag == AST_ACCESS_MEMBER_LIST_T) {
		ast* aaccess = FirstAST(atree);
		ast* amember_list = SecondAST(atree);
		access_level level = ASTCastToAccess(aaccess);
		CLIL_member_list(self, current, amember_list, level);
	}
}

void CLIL_member_list(class_loader* self, il_type* current, ast* amember, access_level level) {
	if(amember->tag == AST_MEMBER_DECL_LIST_T) {
		for(int i=0; i<amember->vchildren->length; i++) {
			CLIL_member_list(self, current, AtAST(amember, i), level);
		}
	} else if(amember->tag == AST_MEMBER_DECL_T) {
		ast* achild = FirstAST(amember);
		if (achild->tag == AST_FIELD_DECL_T) {
			CLIL_field(self, current, achild, level);
		} else if(achild->tag == AST_PROP_DECL_T) {
			CLIL_prop(self, current, achild, level);
		} else if (achild->tag == AST_METHOD_DECL_T) {
			CLIL_method(self, current, achild, level);
		} else if (achild->tag == AST_CONSTRUCTOR_DECL_T) {
			CLIL_ctor(self, current, achild, level);
		} else if(achild->tag == AST_OPERATOR_OVERLOAD_T) {
			CLIL_operator_overload(self, current, achild, level);
		}
	}
}

void CLIL_field(class_loader* self, il_type* current, ast* afield, access_level level) {
	//assert(current->tag == ilTYPE_CLASS_T);
	ast* amodifier = FirstAST(afield);
	ast* atype_name = SecondAST(afield);
	ast* aaccess_name = AtAST(afield, 2);
	ast* afact = AtAST(afield, 3);
	//インターフェイスはフィールドを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_FIELD_T,
			Ref2Str(current->u.interface_->namev),
			Ref2Str(aaccess_name->u.stringv_value)
		);
		return;
	}
	il_field* v = NewILField(aaccess_name->u.stringv_value);
	CLIL_generic_cache(atype_name, v->fqcn);
	bool error;
	v->access = level;
	v->modifier = ASTCastToModifier(amodifier, &error);
	AddFieldILType(current, v);
	//設定されているなら初期値も
	if(!IsBlankAST(afact)) {
		v->initial_value = CLIL_factor(self, afact);
	}
	//重複する修飾子を検出
	if(error) {
		ThrowBCError(BCERROR_OVERWRAP_MODIFIER_T, Ref2Str(v->namev));
	}
}

void CLIL_prop(class_loader* self, il_type* current, ast* aprop, access_level level) {
	ast* amod = AtAST(aprop, 0);
	ast* atypename = AtAST(aprop, 1);
	ast* aset = AtAST(aprop, 2);
	ast* aget = AtAST(aprop, 3);
	string_view propname = aprop->u.stringv_value;
	il_property* ret = il_property_new(propname);
	CLIL_generic_cache(atypename, ret->fqcn);
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
	ret->set = CLIL_prop_body(self, current, aset, ilPROPERTY_SET_T, level);
	ret->get = CLIL_prop_body(self, current, aget, ilPROPERTY_GET_T, level);
	AddPropertyILType(current, ret);
	if(ret->set->is_short != ret->get->is_short) {
		ThrowBCError(BCERROR_INVALID_PROPERTY_DECL_T, Ref2Str(current->u.class_->namev), Ref2Str(propname));
	}
}

void CLIL_method(class_loader* self, il_type* current, ast* amethod, access_level level) {
	assert(current->tag == ilTYPE_CLASS_T || current->tag == ilTYPE_INTERFACE_T);
	ast* amodifier = AtAST(amethod, 0);
	ast* afunc_name = AtAST(amethod, 1);
	ast* ageneric = AtAST(amethod, 2);
	ast* aparam_list = AtAST(amethod, 3);
	ast* afunc_body = AtAST(amethod, 4);
	ast* aret_name = AtAST(amethod, 5);
	il_method* v = NewILMethod(afunc_name->u.stringv_value);
	CLIL_type_parameter(self, ageneric, v->type_parameter_list);
	CLIL_generic_cache(aret_name, v->return_fqcn);
	bool error;
	v->access = level;
	v->modifier = ASTCastToModifier(amodifier, &error);
	CLIL_parameter_list(self, v->parameter_list, aparam_list);
	CLIL_body(self, v->statement_list, afunc_body);
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

void CLIL_ctor(class_loader* self, il_type* current, ast* aconstructor, access_level level) {
	//assert(current->tag == ilTYPE_CLASS_T);
	ast* aparams = AtAST(aconstructor, 0);
	ast* achain = AtAST(aconstructor, 1);
	ast* abody = AtAST(aconstructor, 2);
	il_constructor_chain* ilchain = NULL;
	//インターフェイスはコンストラクタを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_CTOR_T,
			Ref2Str(current->u.interface_->namev)
		);
		return;
	}
	if (!IsBlankAST(achain)) {
		ast* achain_type = FirstAST(achain);
		ast* aargs = SecondAST(achain);
		ilchain = NewILConstructorChain();
		ilchain->type = ASTCastToChainType(achain_type);
		CLIL_argument_list(self, ilchain->argument_list, aargs);
	}
	il_constructor* ilcons = NewILConstructor();
	ilcons->access = level;
	ilcons->chain = ilchain;
	CLIL_parameter_list(self, ilcons->parameter_list, aparams);
	CLIL_body(self, ilcons->statement_list, abody);
	PushVector(current->u.class_->constructor_list, ilcons);
}

void CLIL_operator_overload(class_loader* self, il_type* current, ast* aopov, access_level level) {
	//assert(aopov->tag == AST_OPERATOR_OVERLOAD_T);
	operator_type ot = aopov->u.operator_value;
	ast* aparam_list = AtAST(aopov, 0);
	ast* abody = AtAST(aopov, 1);
	ast* areturn = AtAST(aopov, 2);
	//インターフェイスはコンストラクタを持てない
	if(current->tag == ilTYPE_INTERFACE_T) {
		ThrowBCError(
			BCERROR_INTERFACE_HAS_OPOV_T,
			Ref2Str(current->u.interface_->namev),
			operator_tostring(ot)
		);
		return;
	}
	il_operator_overload* ilopov = NewILOperatorOverload(ot);
	ilopov->access = level;
	CLIL_parameter_list(self, ilopov->parameter_list, aparam_list);
	CLIL_body(self, ilopov->statement_list, abody);
	CLIL_generic_cache(areturn, ilopov->return_fqcn);
	PushVector(current->u.class_->operator_overload_list, ilopov);
}
//private
static il_property_body* CLIL_prop_body(class_loader* self, il_type* current, ast* abody, il_property_body_tag tag, access_level level) {
	il_property_body* ret = il_property_body_new(tag);
	assert(abody->tag == AST_PROP_SET_T || abody->tag == AST_PROP_GET_T);
	ast* aacess = FirstAST(abody);
	ast* astmt_list = SecondAST(abody);
	ret->access = level;
	CLIL_body(self, ret->statement_list, astmt_list);
	if(!IsBlankAST(aacess)) {
		ret->access = aacess->u.access_value;
	}
	if(ret->statement_list->length == 0) {
		ret->is_short = true;
	}
	return ret;
}