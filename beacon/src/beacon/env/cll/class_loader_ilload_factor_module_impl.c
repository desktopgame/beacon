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
	if (source->tag == ast_int_T) {
		return il_factor_wrap_int(il_factor_int_new(source->u.int_value));
	} else if (source->tag == ast_double_T) {
		return il_factor_wrap_double(il_factor_double_new(source->u.double_value));
	} else if (source->tag == ast_char_T) {
		return il_factor_wrap_char(il_factor_char_new(source->u.char_value));
	} else if (source->tag == ast_string_T) {
		return il_factor_wrap_string(il_factor_string_new(source->u.stringv_value));
	} else if (source->tag == ast_variable_T) {
		return il_factor_wrap_variable(CLIL_variable(self, source));
		//operator(+ - * / %)
	} else if (source->tag == ast_add_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_add_T));
	} else if (source->tag == ast_sub_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_sub_T));
	} else if (source->tag == ast_mul_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_mul_T));
	} else if (source->tag == ast_div_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_div_T));
	} else if (source->tag == ast_mod_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_mod_T));
		//operator(| || & &&)
	} else if (source->tag == ast_bit_or_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_bit_or_T));
	} else if (source->tag == ast_logic_or_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_logic_or_T));
	} else if (source->tag == ast_bit_and_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_bit_and_T));
	} else if (source->tag == ast_logic_and_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_logic_and_T));
	//^
	} else if(source->tag == ast_exc_or_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_excor_T));
	} else if(source->tag == ast_childa_T) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_childa_T));
	//<< >>
	} else if(source->tag == ast_lshift_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_lshift_T));
	} else if(source->tag == ast_rshift_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_rshift_T));
	//operator(== != > >= < <=)
	} else if (source->tag == ast_equal_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_eq_T));
	} else if (source->tag == ast_not_Tequal_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_not_eq_T));
	} else if (source->tag == ast_gt_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_gt_T));
	} else if (source->tag == ast_ge_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_ge_T));
	} else if (source->tag == ast_lt_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_lt_T));
	} else if (source->tag == ast_le_T) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_le_T));
		//operator(= += -= *= /= %=)
	} else if (source->tag == ast_as_Tsign_T) {
		return il_factor_wrap_assign(CLIL_assign(self, source));
	} else if (source->tag == ast_add_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_add_T));
	} else if (source->tag == ast_sub_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_sub_T));
	} else if (source->tag == ast_mul_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_mul_T));
	} else if (source->tag == ast_div_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_div_T));
	} else if (source->tag == ast_mod_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_mod_T));
	//instanceof
	} else if(source->tag == ast_instanceof_T) {
		return il_factor_wrap_instanceof(CLIL_instanceof(self, source));
	//|= &=
	} else if(source->tag == ast_or_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_bit_or_T));
	} else if(source->tag == ast_and_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_bit_and_T));
	//<<= >>=
	} else if(source->tag == ast_lshift_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_lshift_T));
	} else if(source->tag == ast_rshift_assign_T) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_rshift_T));
	//!-
	} else if (source->tag == ast_not_T) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_not_T));
	} else if (source->tag == ast_neg_T) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_negative_T));
	} else if(source->tag == ast_explicit_uoperator_T) {
		return il_factor_wrap_explicit_unary_op(CLIL_explicit_unary(self, source, source->u.operator_value));
	} else if(source->tag == ast_explicit_bioperator_T) {
		return il_factor_wrap_explicit_binary_op(CLIL_explicit_binary(self, source, source->u.operator_value));
		//this super
	} else if (source->tag == ast_this_T) {
		il_factor* ret = il_factor_new(ilfactor_this_T);
		il_factor_this* th = il_factor_this_new();
		ret->u.this_ = th;
		return ret;
	} else if (source->tag == ast_super_T) {
		il_factor* ret = il_factor_new(ilfactor_super_T);
		il_factor_super* sp = il_factor_super_new();
		ret->u.super_ = sp;
		return ret;
	} else if (source->tag == ast_new_instance_T) {
		return il_factor_wrap_new_instance(CLIL_new_instance(self, source));
	} else if (source->tag == ast_true_T) {
		return il_factor_wrap_bool(CLIL_true(self, source));
	} else if (source->tag == ast_false_T) {
		return il_factor_wrap_bool(CLIL_false(self, source));
	} else if (source->tag == ast_null_T) {
		il_factor* ret = il_factor_new(ilfactor_null_T);
		ret->u.null_ = NULL;
		return ret;
	} else if (source->tag == ast_as_T) {
		return il_factor_wrap_as(CLIL_as(self, source));
	} else if(source->tag == ast_op_call_T) {
		return il_factor_wrap_call_op(CLIL_call_op(self, source));
	} else if(source->tag == ast_field_access_T) {
		return il_factor_wrap_member_op(CLIL_member_op(self, source));
	} else if(source->tag == ast_subscript_access_T) {
		return il_factor_wrap_subscript(CLIL_subscript(self, source));
	}
	il_factor* fact = il_factor_new(ilfactor_unary_op_T);
	return fact;
}

static il_factor_bool * CLIL_true(class_loader * self, ast * source) {
	return il_factor_bool_new(true);
}

static il_factor_bool * CLIL_false(class_loader * self, ast * source) {
	return il_factor_bool_new(false);
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
	ret->right = il_factor_wrap_binary(bin);
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
	assert(source->tag == ast_new_instance_T);
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
	il_factor_as* ret = il_factor_as_new();
	ret->fact = CLIL_factor(self, FirstAST(source));
	CLIL_generic_cache(SecondAST(source), ret->fqcn);
	return ret;
}

static il_factor_call_op* CLIL_call_op(class_loader* self, ast* source) {
	assert(source->tag == ast_op_call_T);
	il_factor_call_op* ret = il_factor_call_op_new();
	ast* afact = FirstAST(source);
	ast* aargs = SecondAST(source);
	ret->receiver = CLIL_factor(self, afact);
	CLIL_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_member_op* CLIL_member_op(class_loader* self, ast* source) {
	assert(source->tag == ast_field_access_T);
	ast* afact = FirstAST(source);
	ast* aname = SecondAST(source);
	ast* atype_args = AtAST(source, 2);
	il_factor_member_op* ret = il_factor_member_op_new(aname->u.stringv_value);
	ret->fact = CLIL_factor(self, afact);
	CLIL_type_argument(self, atype_args, ret->type_args);
	return ret;
}

static il_factor_instanceof* CLIL_instanceof(class_loader* self, ast* source) {
	assert(source->tag == ast_instanceof_T);
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