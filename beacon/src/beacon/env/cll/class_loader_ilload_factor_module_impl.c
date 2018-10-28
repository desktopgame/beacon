#include "class_loader_ilload_factor_module_impl.h"
#include "../../il/il_factor_impl.h"
#include "../../util/mem.h"
#include "../class_loader.h"
#include "class_loader_ilload_type_module_impl.h"
#include <stdio.h>
//proto
static ILFactor* CLILFactorImpl(ClassLoader* self, AST* source);
static ILBool* CLIL_true(ClassLoader* self, AST* source);
static ILBool* CLIL_false(ClassLoader* self, AST* source);
static ILUnaryOp* CLIL_unary(ClassLoader* self, AST* source, OperatorType type);
static ILBinaryOp* CLIL_binary(ClassLoader* self, AST* source, OperatorType type);
static ILFactor_explicit_unary_op* CLIL_explicit_unary(ClassLoader* self, AST* source, OperatorType type);
static ILFactor_explicit_binary_op* CLIL_explicit_binary(ClassLoader* self, AST* source, OperatorType type);
static ILAssignOp* CLIL_assign(ClassLoader* self, AST* source);
static ILAssignOp* CLIL_assign_arithmetic(ClassLoader* self, AST* source, OperatorType type);
static ILFactor_variable* CLIL_variable(ClassLoader* self, AST* source);
static ILNewInstance* CLIL_new_instance(ClassLoader* self, AST* source);
static ILAs* CLIL_as(ClassLoader* self, AST* source);
static ILFactor_call_op* CLIL_call_op(ClassLoader* self, AST* source);
static ILMemberOp* CLIL_member_op(ClassLoader* self, AST* source);
static ILInstanceOf* CLIL_instanceof(ClassLoader* self, AST* source);
static ILFactor_subscript* CLIL_subscript(ClassLoader* self, AST* source);

ILFactor* CLILFactor(ClassLoader* self, AST* source) {
	ILFactor* ret = CLILFactorImpl(self, source);
	assert(source->Lineno >= 0);
	ret->lineno = source->Lineno;
	return ret;
}


//private
static ILFactor* CLILFactorImpl(ClassLoader* self, AST* source) {
	if (source->Tag == AST_INT_T) {
		return WrapILInt(ILInt_new(source->Attr.IntValue));
	} else if (source->Tag == AST_DOUBLE_T) {
		return WrapILDouble(NewILDouble(source->Attr.DoubleValue));
	} else if (source->Tag == AST_CHAR_T) {
		return WrapILChar(NewILChar(source->Attr.CharValue));
	} else if (source->Tag == AST_STRING_T) {
		return WrapILString(NewILString(source->Attr.StringVValue));
	} else if (source->Tag == AST_VARIABLE_T) {
		return WrapILVariable(CLIL_variable(self, source));
		//operator(+ - * / %)
	} else if (source->Tag == AST_ADD_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_ADD_T));
	} else if (source->Tag == AST_SUB_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_SUB_T));
	} else if (source->Tag == AST_MUL_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_MUL_T));
	} else if (source->Tag == AST_DIV_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_DIV_T));
	} else if (source->Tag == AST_MOD_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_MOD_T));
		//operator(| || & &&)
	} else if (source->Tag == AST_BIT_OR_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_BIT_OR_T));
	} else if (source->Tag == AST_LOGIC_OR_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_LOGIC_OR_T));
	} else if (source->Tag == AST_BIT_AND_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_BIT_AND_T));
	} else if (source->Tag == AST_LOGIC_AND_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_LOGIC_AND_T));
	//^
	} else if(source->Tag == AST_EXC_OR_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_EXCOR_T));
	} else if(source->Tag == AST_CHILDA_T) {
		return WrapILUnaryOp(CLIL_unary(self, source, OPERATOR_CHILDA_T));
	//<< >>
	} else if(source->Tag == AST_LSHIFT_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_LSHIFT_T));
	} else if(source->Tag == AST_RSHIFT_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_RSHIFT_T));
	//operator(== != > >= < <=)
	} else if (source->Tag == AST_EQUAL_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_EQ_T));
	} else if (source->Tag == AST_NOT_TEQUAL_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_NOT_EQ_T));
	} else if (source->Tag == AST_GT_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_GT_T));
	} else if (source->Tag == AST_GE_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_GE_T));
	} else if (source->Tag == AST_LT_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_LT_T));
	} else if (source->Tag == AST_LE_T) {
		return WrapILBinaryOp(CLIL_binary(self, source, OPERATOR_LE_T));
		//operator(= += -= *= /= %=)
	} else if (source->Tag == AST_AS_TSIGN_T) {
		return WrapILAssignOp(CLIL_assign(self, source));
	} else if (source->Tag == AST_ADD_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_ADD_T));
	} else if (source->Tag == AST_SUB_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_SUB_T));
	} else if (source->Tag == AST_MUL_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_MUL_T));
	} else if (source->Tag == AST_DIV_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_DIV_T));
	} else if (source->Tag == AST_MOD_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_MOD_T));
	//instanceof
	} else if(source->Tag == AST_INSTANCEOF_T) {
		return WrapILInstanceOf(CLIL_instanceof(self, source));
	//|= &=
	} else if(source->Tag == AST_OR_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_BIT_OR_T));
	} else if(source->Tag == AST_AND_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_BIT_AND_T));
	//<<= >>=
	} else if(source->Tag == AST_LSHIFT_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_LSHIFT_T));
	} else if(source->Tag == AST_RSHIFT_ASSIGN_T) {
		return WrapILAssignOp(CLIL_assign_arithmetic(self, source, OPERATOR_RSHIFT_T));
	//!-
	} else if (source->Tag == AST_NOT_T) {
		return WrapILUnaryOp(CLIL_unary(self, source, OPERATOR_NOT_T));
	} else if (source->Tag == AST_NEG_T) {
		return WrapILUnaryOp(CLIL_unary(self, source, OPERATOR_NEGATIVE_T));
	} else if(source->Tag == AST_EXPLICIT_UOPERATOR_T) {
		return WrapILExplicitUnaryOp(CLIL_explicit_unary(self, source, source->Attr.OperatorValue));
	} else if(source->Tag == AST_EXPLICIT_BIOPERATOR_T) {
		return WrapILExplicitBinaryOp(CLIL_explicit_binary(self, source, source->Attr.OperatorValue));
		//this super
	} else if (source->Tag == AST_THIS_T) {
		ILFactor* ret = ILFactor_new(ILFACTOR_THIS_T);
		ILThis* th = NewILThis();
		ret->u.this_ = th;
		return ret;
	} else if (source->Tag == AST_SUPER_T) {
		ILFactor* ret = ILFactor_new(ILFACTOR_SUPER_T);
		ILSuper* sp = NewILSuper();
		ret->u.super_ = sp;
		return ret;
	} else if (source->Tag == AST_NEW_INSTANCE_T) {
		return WrapILNewInstance(CLIL_new_instance(self, source));
	} else if (source->Tag == AST_TRUE_T) {
		return WrapILBool(CLIL_true(self, source));
	} else if (source->Tag == AST_FALSE_T) {
		return WrapILBool(CLIL_false(self, source));
	} else if (source->Tag == AST_NULL_T) {
		ILFactor* ret = ILFactor_new(ILFACTOR_NULL_T);
		ret->u.null_ = NULL;
		return ret;
	} else if (source->Tag == AST_AS_T) {
		return WrapILAs(CLIL_as(self, source));
	} else if(source->Tag == AST_OP_CALL_T) {
		return WrapCallOp(CLIL_call_op(self, source));
	} else if(source->Tag == AST_FIELD_ACCESS_T) {
		return WrapILMemberOp(CLIL_member_op(self, source));
	} else if(source->Tag == AST_SUBSCRIPT_ACCESS_T) {
		return WrapILSubscript(CLIL_subscript(self, source));
	}
	ILFactor* fact = ILFactor_new(ILFACTOR_UNARY_OP_T);
	return fact;
}

static ILBool * CLIL_true(ClassLoader * self, AST* source) {
	return NewILBool(true);
}

static ILBool * CLIL_false(ClassLoader * self, AST* source) {
	return NewILBool(false);
}

static ILUnaryOp* CLIL_unary(ClassLoader* self, AST* source, OperatorType type) {
	ILUnaryOp* ret = NewILUnaryOp(type);
	AST* a = FirstAST(source);
	ret->Arg = CLILFactor(self, a);
	return ret;
}

static ILBinaryOp* CLIL_binary(ClassLoader* self, AST* source, OperatorType type) {
	ILBinaryOp* ret = NewILBinaryOp(type);
	AST* aleft = FirstAST(source);
	AST* aright = SecondAST(source);
	ret->Left = CLILFactor(self, aleft);
	ret->Right = CLILFactor(self, aright);
	return ret;
}

static ILFactor_explicit_unary_op* CLIL_explicit_unary(ClassLoader* self, AST* source, OperatorType type) {
	ILFactor_explicit_unary_op* ret = NewILExplicitUnaryOp(type);
	ret->receiver = CLILFactor(self, FirstAST(source));
	return ret;
}

static ILFactor_explicit_binary_op* CLIL_explicit_binary(ClassLoader* self, AST* source, OperatorType type) {
	ILFactor_explicit_binary_op* ret = NewILExplicitBinaryOp(type);
	ret->receiver = CLILFactor(self, FirstAST(source));
	ret->arg = CLILFactor(self, SecondAST(source));
	return ret;
}

static ILAssignOp* CLIL_assign(ClassLoader* self, AST* source) {
	ILAssignOp* ret = NewILAssignOp();
	AST* aleft = FirstAST(source);
	AST* aright = SecondAST(source);
	ret->Left = CLILFactor(self, aleft);
	ret->Right = CLILFactor(self, aright);
	return ret;
}

static ILAssignOp* CLIL_assign_arithmetic(ClassLoader* self, AST* source, OperatorType type) {
	//a += b
	ILAssignOp* ret = NewILAssignOp();
	ILBinaryOp* bin = NewILBinaryOp(type);
	AST* aleft = FirstAST(source);
	AST* aright = SecondAST(source);
	bin->Left = CLILFactor(self, aleft);
	bin->Right = CLILFactor(self, aright);
	ret->Left = CLILFactor(self, aleft);
	ret->Right = WrapILBinaryOp(bin);
	ret->Right->lineno = aright->Lineno;
	return ret;
}

static ILFactor_variable* CLIL_variable(ClassLoader* self, AST* source) {
	AST* afqcn = FirstAST(source);
	AST* atype_args = SecondAST(source);

	ILFactor_variable* ilvar = ILFactor_variable_new();
	CLILFQCNCache(afqcn, ilvar->fqcn);
	CLILTypeArgument(self, atype_args, ilvar->type_args);
	return ilvar;
}

static ILNewInstance* CLIL_new_instance(ClassLoader* self, AST* source) {
	assert(source->Tag == AST_NEW_INSTANCE_T);
	AST* afqcn = FirstAST(source);
	AST* atype_args = SecondAST(source);
	AST* aargs = AtAST(source, 2);
	ILNewInstance* ret = NewILNewInstance();
	CLILFQCNCache(afqcn, ret->FQCNCache);
	CLILTypeArgument(self, atype_args, ret->TypeArgs);
	CLILArgumentList(self, ret->Arguments, aargs);
	return ret;
}

static ILAs* CLIL_as(ClassLoader* self, AST* source) {
	ILAs* ret = NewILAs();
	ret->Source = CLILFactor(self, FirstAST(source));
	CLILGenericCache(SecondAST(source), ret->GCache);
	return ret;
}

static ILFactor_call_op* CLIL_call_op(ClassLoader* self, AST* source) {
	assert(source->Tag == AST_OP_CALL_T);
	ILFactor_call_op* ret = NewILCallOp();
	AST* afact = FirstAST(source);
	AST* aargs = SecondAST(source);
	ret->receiver = CLILFactor(self, afact);
	CLILArgumentList(self, ret->argument_list, aargs);
	return ret;
}

static ILMemberOp* CLIL_member_op(ClassLoader* self, AST* source) {
	assert(source->Tag == AST_FIELD_ACCESS_T);
	AST* afact = FirstAST(source);
	AST* aname = SecondAST(source);
	AST* atype_args = AtAST(source, 2);
	ILMemberOp* ret = NewILMemberOp(aname->Attr.StringVValue);
	ret->Source = CLILFactor(self, afact);
	CLILTypeArgument(self, atype_args, ret->TypeArgs);
	return ret;
}

static ILInstanceOf* CLIL_instanceof(ClassLoader* self, AST* source) {
	assert(source->Tag == AST_INSTANCEOF_T);
	AST* afact = FirstAST(source);
	AST* atype = SecondAST(source);
	ILInstanceOf* ret = NewILInstanceOf();
	ret->Source = CLILFactor(self, afact);
	CLILGenericCache(atype, ret->GCache);
	return ret;
}

static ILFactor_subscript* CLIL_subscript(ClassLoader* self, AST* source) {
	ILFactor_subscript* ret = ILFactor_subscript_new();
	AST* afact = FirstAST(source);
	AST* apos = SecondAST(source);
	ret->receiver = CLILFactor(self, afact);
	ret->pos = CLILFactor(self, apos);
	return ret;
}