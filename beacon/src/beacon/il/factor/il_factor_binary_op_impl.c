#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include "../il_factor_impl.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../util/mem.h"
#include "binary/il_factor_arithmetic_op_impl.h"
#include "binary/il_factor_compare_op_impl.h"
//#include "binary/il_factor_assign_op_impl.h"
#include "binary/il_factor_logic_op_impl.h"

//proto
static char* il_factor_binary_op_optostr(il_factor_binary_op* self);
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, operator_type c);
static opcode bi_operator_to_opi(operator_type type);
static opcode bi_operator_to_opd(operator_type type);
static opcode bi_operator_to_opb(operator_type type);
static bool ilbi_compare(il_factor_binary_op* self);

il_factor * il_factor_wrap_binary(il_factor_binary_op * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_binary_op;
	ret->u.binary_ = self;
	return ret;
}

il_factor_binary_op * il_factor_binary_op_new(operator_type type) {
	il_factor_binary_op* ret = (il_factor_binary_op*)MEM_MALLOC(sizeof(il_factor_binary_op));
	ret->type = type;
	ret->left = NULL;
	ret->right = NULL;
	return ret;
}

void il_factor_binary_op_dump(il_factor_binary_op * self, int depth) {
	text_putindent(depth);
	text_printf("%s", il_factor_binary_op_optostr(self));
	text_putline();
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env) {
	il_factor_binary_op_generate_impl(self, env, self->type);
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env) {
	il_factor_load(self->left, env);
	il_factor_load(self->right, env);
	//カテゴリーわけ
	if(operator_arithmetic(self->type)) {
		self->category = operator_carithmeric;
		il_factor_arithmetic_op* arith = il_factor_arithmetic_op_new(self->type);
		arith->parent = self;
		self->u.arithmetic_op = arith;
	} else if(operator_compare(self->type)) {
		self->category = operator_ccompare;
		il_factor_compare_op* comp = il_factor_compare_op_new(self->type);
		comp->parent = self;
		self->u.compare_op = comp;
	} else if(operator_bit(self->type) || operator_logic(self->type)) {
		self->category = operator_clogic;
		il_factor_logic_op* logic = il_factor_logic_op_new(self->type);
		logic->parent = self;
		self->u.logic_op = logic;
	}
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env) {
	generic_type* ltype = il_factor_eval(self->left, env);
	generic_type* rtype = il_factor_eval(self->right, env);
	//左辺か右辺を解釈できなかった
	if(il_error_panic()) {
		return NULL;
	}
	if (ltype->core_type == TYPE_INT &&
		rtype->core_type == TYPE_INT) {
		if (ilbi_compare(self)) {
			return GENERIC_BOOL;
		}
		return GENERIC_INT;
	}
	if (ltype->core_type == TYPE_DOUBLE &&
		rtype->core_type == TYPE_DOUBLE) {
		if (ilbi_compare(self)) {
			return GENERIC_BOOL;
		}
		return GENERIC_DOUBLE;
	}
	if (ltype->core_type == TYPE_BOOL &&
		rtype->core_type == TYPE_BOOL) {
		return GENERIC_BOOL;
	}
	return NULL;
}

char* il_factor_binary_op_tostr(il_factor_binary_op* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	char* left = il_factor_tostr(self->left, env);
	char* right = il_factor_tostr(self->right, env);
	string_buffer_appendf(sb, "%s %s %s", left, il_factor_binary_op_optostr(self), right);
	MEM_FREE(left);
	MEM_FREE(right);
	return string_buffer_release(sb);
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}

//private
static char* il_factor_binary_op_optostr(il_factor_binary_op* self) {
	switch(self->type) {
		case operator_add: return "+";
		case operator_sub: return "-";
		case operator_mul: return "*";
		case operator_div: return "/";
		case operator_mod: return "%%";
		case operator_bit_or: return "|";
		case operator_logic_or: return "||";
		case operator_eq: return "==";
		case operator_noteq: return "!=";
		case operator_lshift: return "<<";
		case operator_rshift: return ">>";
		case operator_excor: return "^";
		default: return "NULL";
	}
}

static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, operator_type c) {
	//ここで逆にしておく
	il_factor_generate(self->right, env);
	il_factor_generate(self->left, env);
	int counts = 0;
	generic_type* ltype = (generic_type*)il_factor_eval(self->left, env);
	generic_type* rtype = (generic_type*)il_factor_eval(self->right, env);
	if (generic_type_int(ltype) &&
		generic_type_int(rtype)) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opi(c));
		counts++;
	}
	if (generic_type_double(ltype) &&
		generic_type_double(rtype)) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opd(c));
		counts++;
	}
	if (generic_type_bool(ltype) &&
		generic_type_bool(rtype)) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opb(c));
		counts++;
	}
	assert(counts > 0);
}

static opcode bi_operator_to_opi(operator_type type) {
	switch (type) {
		case operator_add: return op_iadd;
		case operator_sub: return op_isub;
		case operator_mul: return op_imul;
		case operator_div: return op_idiv;
		case operator_mod: return op_imod;

		case operator_bit_or: return op_ibit_or;
		case operator_logic_or: return op_ilogic_or;
		case operator_bit_and: return op_ibit_and;
		case operator_logic_and: return op_ilogic_and;

		case operator_eq: return op_ieq;
		case operator_noteq: return op_inoteq;
		case operator_gt: return op_igt;
		case operator_ge: return op_ige;
		case operator_lt: return op_ilt;
		case operator_le: return op_ile;

		case operator_lshift: return op_ilsh;
		case operator_rshift: return op_irsh;
		case operator_excor: return op_iexcor;
		default: return -1;
	}
}

static opcode bi_operator_to_opd(operator_type type) {
	switch (type) {
		case operator_add: return op_dadd;
		case operator_sub: return op_dsub;
		case operator_mul: return op_dmul;
		case operator_div: return op_ddiv;
		case operator_mod: return op_dmod;

		case operator_bit_or:
		case operator_logic_or:
		case operator_bit_and:
		case operator_logic_and:
			//未対応
			assert(false);
			break;

		case operator_eq: return op_deq;
		case operator_noteq: return op_dnoteq;
		case operator_gt: return op_dgt;
		case operator_ge: return op_dge;
		case operator_lt: return op_dlt;
		case operator_le: return op_dle;

		case operator_lshift:
		case operator_rshift:
		case operator_excor:
			assert(false);
			break;
		default: return -1;
	}
}

static opcode bi_operator_to_opb(operator_type type) {
	switch (type) {
		case operator_bit_or: return op_bbit_or;
		case operator_logic_or: return op_blogic_or;
		case operator_bit_and: return op_bbit_and;
		case operator_logic_and: return op_blogic_and;

		default:
			assert(false);
			break;
	}
}

static bool ilbi_compare(il_factor_binary_op* self) {
	operator_type t = self->type;
	switch (t) {
		case operator_eq:
		case operator_noteq:
		case operator_gt:
		case operator_ge:
		case operator_lt:
		case operator_le:
			return true;
		default:
			break;
	}
	return false;
}

il_factor_binary_op* il_factor_cast_binary_op(il_factor* fact) {
	assert(fact->type == ilfactor_binary_op);
	return fact->u.binary_;
}