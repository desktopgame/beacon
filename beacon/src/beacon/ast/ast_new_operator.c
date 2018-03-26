#include "ast_new_operator.h"
#include <stdlib.h>
//proto
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r);
static ast* ast_new_uop(ast_tag tag, ast* a);

ast* ast_new_unary(ast_tag tag, ast* a) {
	ast* ret = ast_new(tag);
	ast_push(ret, a);
	return ret;
}

ast* ast_new_binary(ast_tag tag, ast* left, ast* right) {
	ast* ret = ast_new(tag);
	ast_push(ret, left);
	ast_push(ret, right);
	return ret;
}

ast * ast_new_add(ast * l, ast * r) {
	return ast_new_bop(ast_add, l, r);
}

ast * ast_new_sub(ast * l, ast * r) {
	return ast_new_bop(ast_sub, l, r);
}

ast * ast_new_mul(ast * l, ast * r) {
	return ast_new_bop(ast_mul, l, r);
}

ast * ast_new_div(ast * l, ast * r) {
	return ast_new_bop(ast_div, l, r);
}

ast * ast_new_mod(ast * l, ast * r) {
	return ast_new_bop(ast_mod, l, r);
}

ast * ast_new_generic_assign(ast * l, assign_operator_type type, ast * r) {
	switch (type) {
		case assign_otype_def:
			return ast_new_assign(l, r);
			break;

		case assign_otype_add:
			return ast_new_add_assign(l, r);
			break;

		case assign_otype_sub:
			return ast_new_sub_assign(l, r);
			break;

		case assign_otype_mul:
			return ast_new_mul_assign(l, r);
			break;

		case assign_otype_div:
			return ast_new_div_assign(l, r);
			break;

		case assign_otype_mod:
			return ast_new_mod_assign(l, r);
			break;
		default:
			break;
	}
	return NULL;
}

ast * ast_new_assign(ast * l, ast * r) {
	return ast_new_bop(ast_assign, l, r);
}

ast * ast_new_add_assign(ast * l, ast * r) {
	return ast_new_bop(ast_add_assign, l, r);
}

ast * ast_new_sub_assign(ast * l, ast * r) {
	return ast_new_bop(ast_sub_assign, l, r);
}

ast * ast_new_mul_assign(ast * l, ast * r) {
	return ast_new_bop(ast_mul_assign, l, r);
}

ast * ast_new_div_assign(ast * l, ast * r) {
	return ast_new_bop(ast_div_assign, l, r);
}

ast * ast_new_mod_assign(ast * l, ast * r) {
	return ast_new_bop(ast_mod_assign, l, r);
}

ast * ast_new_bit_or(ast * l, ast * r) {
	return ast_new_bop(ast_bit_or, l, r);
}

ast * ast_new_logic_or(ast * l, ast * r) {
	return ast_new_bop(ast_logic_or, l, r);
}

ast * ast_new_bit_and(ast * l, ast * r) {
	return ast_new_bop(ast_bit_and, l, r);
}

ast * ast_new_logic_and(ast * l, ast * r) {
	return ast_new_bop(ast_logic_and, l, r);
}

ast * ast_new_equal(ast * l, ast * r) {
	return ast_new_bop(ast_equal, l, r);
}

ast * ast_new_notequal(ast * l, ast * r) {
	return ast_new_bop(ast_notequal, l, r);
}

ast * ast_new_gt(ast * l, ast * r) {
	return ast_new_bop(ast_gt, l, r);
}

ast * ast_new_ge(ast * l, ast * r) {
	return ast_new_bop(ast_ge, l, r);
}

ast * ast_new_lt(ast * l, ast * r) {
	return ast_new_bop(ast_lt, l, r);
}

ast * ast_new_le(ast * l, ast * r) {
	return ast_new_bop(ast_le, l, r);
}

ast * ast_new_not(ast * a) {
	return ast_new_uop(ast_not, a);
}

ast * ast_new_neg(ast * a) {
	return ast_new_uop(ast_neg, a);
}

//private
static ast* ast_new_bop(ast_tag tag, ast* l, ast* r) {
	ast* ret = ast_new(tag);
	ast_push(ret, l);
	ast_push(ret, r);
	return ret;
}

static ast* ast_new_uop(ast_tag tag, ast* a) {
	ast* ret = ast_new(tag);
	ast_push(ret, a);
	return ret;
}