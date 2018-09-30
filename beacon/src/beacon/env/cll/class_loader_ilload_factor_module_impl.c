#include "class_loader_ilload_factor_module_impl.h"
#include "../../il/il_factor_impl.h"
#include "../../util/mem.h"
#include "../class_loader.h"
#include "class_loader_ilload_type_module_impl.h"
#include <stdio.h>
//proto
static il_factor* CLIL_factorImpl(class_loader* self, ast* source);
static il_factor_bool* CLIL_true(class_loader* self, ast* source);
static il_factor_bool* CLIL_false(class_loader* self, ast* source);
static il_factor_unary_op* CLIL_unary(class_loader* self, ast* source, operator_type type);
static il_factor_binary_op* CLIL_binary(class_loader* self, ast* source, operator_type type);
static il_factor_explicit_unary_op* CLIL_explicit_unary(class_loader* self, ast* source, operator_type type);
static il_factor_explicit_binary_op* CLIL_explicit_binary(class_loader* self, ast* source, operator_type type);
static il_factor_assign_op* CLIL_assign(class_loader* self, ast* source);
static il_factor_assign_op* CLIL_assign_arithmetic(class_loader* self, ast* source, operator_type type);
static il_factor_variable* CLIL_variable(class_loader* self, ast* source);
static il_factor_new_instance* CLIL_new_instance(class_loader* self, ast* source);
static il_factor_as* CLIL_as(class_loader* self, ast* source);
static il_factor_call_op* CLIL_call_op(class_loader* self, ast* source);
static il_factor_member_op* CLIL_member_op(class_loader* self, ast* source);
static il_factor_instanceof* CLIL_instanceof(class_loader* self, ast* source);
static il_factor_subscript* CLIL_subscript(class_loader* self, ast* source);

il_factor* CLIL_factor(class_loader* self, ast* source) {
	il_factor* ret = CLIL_factorImpl(self, source);
	assert(source->lineno >= 0);
	ret->lineno = source->lineno;
	return ret;
}


//private
static il_factor* CLIL_factorImpl(class_loader* self, ast* source) {
	if (source->tag == AST_INT_T) {
		return WrapILInt(il_factor_int_new(source->u.int_value));
	} else if (source->tag == AST_DOUBLE_T) {
		return WrapILDouble(NewILDouble(source->u.double_value));
	} else if (source->tag == AST_CHAR_T) {
		return WrapILChar(NewILChar(source->u.char_value));
	} else if (source->tag == AST_STRING_T) {
		return WrapILString(NewILString(source->u.stringv_value));
	} else if (source->tag == AST_VARIABLE_T) {
		return il_factor_wrap_variable(CLIL_variable(self, source));
		//operator(+ - * / %)
	} else if (source->tag == AST_ADD_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_ADD_T));
	} else if (source->tag == AST_SUB_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_SUB_T));
	} else if (source->tag == AST_MUL_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_MUL_T));
	} else if (source->tag == AST_DIV_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_DIV_T));
	} else if (source->tag == AST_MOD_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_MOD_T));
		//operator(| || & &&)
	} else if (source->tag == AST_BIT_OR_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_BIT_OR_T));
	} else if (source->tag == AST_LOGIC_OR_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_LOGIC_OR_T));
	} else if (source->tag == AST_BIT_AND_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_BIT_AND_T));
	} else if (source->tag == AST_LOGIC_AND_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_LOGIC_AND_T));
	//^
	} else if(source->tag == AST_EXC_OR_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_EXCOR_T));
	} else if(source->tag == AST_CHILDA_T) {
		return WrapILUnary(CLIL_unary(self, source, OPERATOR_CHILDA_T));
	//<< >>
	} else if(source->tag == AST_LSHIFT_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_LSHIFT_T));
	} else if(source->tag == AST_RSHIFT_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_RSHIFT_T));
	//operator(== != > >= < <=)
	} else if (source->tag == AST_EQUAL_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_EQ_T));
	} else if (source->tag == AST_NOT_TEQUAL_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_NOT_EQ_T));
	} else if (source->tag == AST_GT_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_GT_T));
	} else if (source->tag == AST_GE_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_GE_T));
	} else if (source->tag == AST_LT_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_LT_T));
	} else if (source->tag == AST_LE_T) {
		return WrapILBinary(CLIL_binary(self, source, OPERATOR_LE_T));
		//operator(= += -= *= /= %=)
	} else if (source->tag == AST_AS_TSIGN_T) {
		return WrapILAssign(CLIL_assign(self, source));
	} else if (source->tag == AST_ADD_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_ADD_T));
	} else if (source->tag == AST_SUB_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_SUB_T));
	} else if (source->tag == AST_MUL_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_MUL_T));
	} else if (source->tag == AST_DIV_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_DIV_T));
	} else if (source->tag == AST_MOD_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_MOD_T));
	//instanceof
	} else if(source->tag == AST_INSTANCEOF_T) {
		return il_factor_wrap_instanceof(CLIL_instanceof(self, source));
	//|= &=
	} else if(source->tag == AST_OR_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_BIT_OR_T));
	} else if(source->tag == AST_AND_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_BIT_AND_T));
	//<<= >>=
	} else if(source->tag == AST_LSHIFT_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_LSHIFT_T));
	} else if(source->tag == AST_RSHIFT_ASSIGN_T) {
		return WrapILAssign(CLIL_assign_arithmetic(self, source, OPERATOR_RSHIFT_T));
	//!-
	} else if (source->tag == AST_NOT_T) {
		return WrapILUnary(CLIL_unary(self, source, OPERATOR_NOT_T));
	} else if (source->tag == AST_NEG_T) {
		return WrapILUnary(CLIL_unary(self, source, OPERATOR_NEGATIVE_T));
	} else if(source->tag == AST_EXPLICIT_UOPERATOR_T) {
		return il_factor_wrap_explicit_unary_op(CLIL_explicit_unary(self, source, source->u.operator_value));
	} else if(source->tag == AST_EXPLICIT_BIOPERATOR_T) {
		return il_factor_wrap_explicit_binary_op(CLIL_explicit_binary(self, source, source->u.operator_value));
		//this super
	} else if (source->tag == AST_THIS_T) {
		il_factor* ret = il_factor_new(ILFACTOR_THIS_T);
		il_factor_this* th = NewILThis();
		ret->u.this_ = th;
		return ret;
	} else if (source->tag == AST_SUPER_T) {
		il_factor* ret = il_factor_new(ILFACTOR_SUPER_T);
		il_factor_super* sp = NewILSuper();
		ret->u.super_ = sp;
		return ret;
	} else if (source->tag == AST_NEW_INSTANCE_T) {
		return il_factor_wrap_new_instance(CLIL_new_instance(self, source));
	} else if (source->tag == AST_TRUE_T) {
		return WrapILBool(CLIL_true(self, source));
	} else if (source->tag == AST_FALSE_T) {
		return WrapILBool(CLIL_false(self, source));
	} else if (source->tag == AST_NULL_T) {
		il_factor* ret = il_factor_new(ILFACTOR_NULL_T);
		ret->u.null_ = NULL;
		return ret;
	} else if (source->tag == AST_AS_T) {
		return WrapILAs(CLIL_as(self, source));
	} else if(source->tag == AST_OP_CALL_T) {
		return il_factor_wrap_call_op(CLIL_call_op(self, source));
	} else if(source->tag == AST_FIELD_ACCESS_T) {
		return il_factor_wrap_member_op(CLIL_member_op(self, source));
	} else if(source->tag == AST_SUBSCRIPT_ACCESS_T) {
		return il_factor_wrap_subscript(CLIL_subscript(self, source));
	}
	il_factor* fact = il_factor_new(ILFACTOR_UNARY_OP_T);
	return fact;
}

static il_factor_bool * CLIL_true(class_loader * self, ast * source) {
	return NewILBool(true);
}

static il_factor_bool * CLIL_false(class_loader * self, ast * source) {
	return NewILBool(false);
}

static il_factor_unary_op* CLIL_unary(class_loader* self, ast* source, operator_type type) {
	il_factor_unary_op* ret = il_factor_unary_op_new(type);
	ast* a = FirstAST(source);
	ret->a = CLIL_factor(self, a);
	return ret;
}

static il_factor_binary_op* CLIL_binary(class_loader* self, ast* source, operator_type type) {
	il_factor_binary_op* ret = il_factor_binary_op_new(type);
	ast* aleft = FirstAST(source);
	ast* aright = SecondAST(source);
	ret->left = CLIL_factor(self, aleft);
	ret->right = CLIL_factor(self, aright);
	return ret;
}

static il_factor_explicit_unary_op* CLIL_explicit_unary(class_loader* self, ast* source, operator_type type) {
	il_factor_explicit_unary_op* ret = il_factor_explicit_unary_op_new(type);
	ret->receiver = CLIL_factor(self, FirstAST(source));
	return ret;
}

static il_factor_explicit_binary_op* CLIL_explicit_binary(class_loader* self, ast* source, operator_type type) {
	il_factor_explicit_binary_op* ret = il_factor_explicit_binary_op_new(type);
	ret->receiver = CLIL_factor(self, FirstAST(source));
	ret->arg = CLIL_factor(self, SecondAST(source));
	return ret;
}

static il_factor_assign_op* CLIL_assign(class_loader* self, ast* source) {
	il_factor_assign_op* ret = il_factor_assign_op_new();
	ast* aleft = FirstAST(source);
	ast* aright = SecondAST(source);
	ret->left = CLIL_factor(self, aleft);
	ret->right = CLIL_factor(self, aright);
	return ret;
}

static il_factor_assign_op* CLIL_assign_arithmetic(class_loader* self, ast* source, operator_type type) {
	//a += b
	il_factor_assign_op* ret = il_factor_assign_op_new();
	il_factor_binary_op* bin = il_factor_binary_op_new(type);
	ast* aleft = FirstAST(source);
	ast* aright = SecondAST(source);
	bin->left = CLIL_factor(self, aleft);
	bin->right = CLIL_factor(self, aright);
	ret->left = CLIL_factor(self, aleft);
	ret->right = WrapILBinary(bin);
	ret->right->lineno = aright->lineno;
	return ret;
}

static il_factor_variable* CLIL_variable(class_loader* self, ast* source) {
	ast* afqcn = FirstAST(source);
	ast* atype_args = SecondAST(source);

	il_factor_variable* ilvar = il_factor_variable_new();
	CLIL_fqcn_cache(afqcn, ilvar->fqcn);
	CLIL_type_argument(self, atype_args, ilvar->type_args);
	return ilvar;
}

static il_factor_new_instance* CLIL_new_instance(class_loader* self, ast* source) {
	assert(source->tag == AST_NEW_INSTANCE_T);
	ast* afqcn = FirstAST(source);
	ast* atype_args = SecondAST(source);
	ast* aargs = AtAST(source, 2);
	il_factor_new_instance* ret = il_factor_new_instance_new();
	CLIL_fqcn_cache(afqcn, ret->fqcnc);
	CLIL_type_argument(self, atype_args, ret->type_args);
	CLIL_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_as* CLIL_as(class_loader* self, ast* source) {
	il_factor_as* ret = NewILAs();
	ret->fact = CLIL_factor(self, FirstAST(source));
	CLIL_generic_cache(SecondAST(source), ret->fqcn);
	return ret;
}

static il_factor_call_op* CLIL_call_op(class_loader* self, ast* source) {
	assert(source->tag == AST_OP_CALL_T);
	il_factor_call_op* ret = NewILCallOp();
	ast* afact = FirstAST(source);
	ast* aargs = SecondAST(source);
	ret->receiver = CLIL_factor(self, afact);
	CLIL_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_member_op* CLIL_member_op(class_loader* self, ast* source) {
	assert(source->tag == AST_FIELD_ACCESS_T);
	ast* afact = FirstAST(source);
	ast* aname = SecondAST(source);
	ast* atype_args = AtAST(source, 2);
	il_factor_member_op* ret = il_factor_member_op_new(aname->u.stringv_value);
	ret->fact = CLIL_factor(self, afact);
	CLIL_type_argument(self, atype_args, ret->type_args);
	return ret;
}

static il_factor_instanceof* CLIL_instanceof(class_loader* self, ast* source) {
	assert(source->tag == AST_INSTANCEOF_T);
	ast* afact = FirstAST(source);
	ast* atype = SecondAST(source);
	il_factor_instanceof* ret = il_factor_instanceof_new();
	ret->fact = CLIL_factor(self, afact);
	CLIL_generic_cache(atype, ret->gcache);
	return ret;
}

static il_factor_subscript* CLIL_subscript(class_loader* self, ast* source) {
	il_factor_subscript* ret = il_factor_subscript_new();
	ast* afact = FirstAST(source);
	ast* apos = SecondAST(source);
	ret->receiver = CLIL_factor(self, afact);
	ret->pos = CLIL_factor(self, apos);
	return ret;
}