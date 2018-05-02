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

//proto
static char* il_factor_binary_op_optostr(il_factor_binary_op* self);
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_context* ilctx, ilbinary_op_type c);
static opcode bi_operator_to_opi(ilbinary_op_type type);
static opcode bi_operator_to_opd(ilbinary_op_type type);
static opcode bi_operator_to_opb(ilbinary_op_type type);
static bool ilbi_compare(il_factor_binary_op* self);

il_factor * il_factor_wrap_binary(il_factor_binary_op * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_binary_op;
	ret->u.binary_ = self;
	return ret;
}

il_factor_binary_op * il_factor_binary_op_new(ilbinary_op_type type) {
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

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env, il_context* ilctx) {
	il_factor_binary_op_generate_impl(self, env, ilctx, self->type);
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env, il_context* ilctx) {
	il_factor_load(self->left, env, ilctx);
	il_factor_load(self->right, env, ilctx);
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env, il_context* ilctx) {
	generic_type* ltype = il_factor_eval(self->left, env, ilctx);
	generic_type* rtype = il_factor_eval(self->right, env, ilctx);
	//左辺か右辺を解釈できなかった
	if(il_error_panic()) {
		return NULL;
	}
	if (ltype->core_type == CL_INT &&
		rtype->core_type == CL_INT) {
		if (ilbi_compare(self)) {
			return GEN_BOOL;
		}
		return GEN_INT;
	}
	if (ltype->core_type == CL_DOUBLE &&
		rtype->core_type == CL_DOUBLE) {
		if (ilbi_compare(self)) {
			return GEN_BOOL;
		}
		return GEN_DOUBLE;
	}
	if (ltype->core_type == CL_BOOL &&
		rtype->core_type == CL_BOOL) {
		return GEN_BOOL;
	}
	return NULL;
}

char* il_factor_binary_op_tostr(il_factor_binary_op* self, enviroment* env, il_context* ilctx) {
	string_buffer* sb = string_buffer_new();
	char* left = il_factor_tostr(self->left, env, ilctx);
	char* right = il_factor_tostr(self->right, env, ilctx);
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
		case ilbinary_add: return "+";
		case ilbinary_sub: return "-";
		case ilbinary_mul: return "*";
		case ilbinary_div: return "/";
		case ilbinary_mod: return "%%";
		case ilbinary_bit_or: return "|";
		case ilbinary_logic_or: return "||";
		case ilbinary_eq: return "==";
		case ilbinary_noteq: return "!=";
		case ilbinary_lshift: return "<<";
		case ilbinary_rshift: return ">>";
		case ilbinary_excor: return "^";
		default: return "NULL";
	}
}

static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_context* ilctx, ilbinary_op_type c) {
	//ここで逆にしておく
	il_factor_generate(self->right, env, ilctx);
	il_factor_generate(self->left, env, ilctx);
	int counts = 0;
	generic_type* ltype = (generic_type*)il_factor_eval(self->left, env, ilctx);
	generic_type* rtype = (generic_type*)il_factor_eval(self->right, env, ilctx);
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

static opcode bi_operator_to_opi(ilbinary_op_type type) {
	switch (type) {
		case ilbinary_add: return op_iadd;
		case ilbinary_sub: return op_isub;
		case ilbinary_mul: return op_imul;
		case ilbinary_div: return op_idiv;
		case ilbinary_mod: return op_imod;

		case ilbinary_bit_or: return op_ibit_or;
		case ilbinary_logic_or: return op_ilogic_or;
		case ilbinary_bit_and: return op_ibit_and;
		case ilbinary_logic_and: return op_ilogic_and;

		case ilbinary_eq: return op_ieq;
		case ilbinary_noteq: return op_inoteq;
		case ilbinary_gt: return op_igt;
		case ilbinary_ge: return op_ige;
		case ilbinary_lt: return op_ilt;
		case ilbinary_le: return op_ile;

		case ilbinary_lshift: return op_ilsh;
		case ilbinary_rshift: return op_irsh;
		case ilbinary_excor: return op_iexcor;
		default: return -1;
	}
}

static opcode bi_operator_to_opd(ilbinary_op_type type) {
	switch (type) {
		case ilbinary_add: return op_dadd;
		case ilbinary_sub: return op_dsub;
		case ilbinary_mul: return op_dmul;
		case ilbinary_div: return op_ddiv;
		case ilbinary_mod: return op_dmod;

		case ilbinary_bit_or:
		case ilbinary_logic_or:
		case ilbinary_bit_and:
		case ilbinary_logic_and:
			//未対応
			assert(false);
			break;

		case ilbinary_eq: return op_deq;
		case ilbinary_noteq: return op_dnoteq;
		case ilbinary_gt: return op_dgt;
		case ilbinary_ge: return op_dge;
		case ilbinary_lt: return op_dlt;
		case ilbinary_le: return op_dle;

		case ilbinary_lshift:
		case ilbinary_rshift:
		case ilbinary_excor:
			assert(false);
			break;
		default: return -1;
	}
}

static opcode bi_operator_to_opb(ilbinary_op_type type) {
	switch (type) {
		case ilbinary_bit_or: return op_bbit_or;
		case ilbinary_logic_or: return op_blogic_or;
		case ilbinary_bit_and: return op_bbit_and;
		case ilbinary_logic_and: return op_blogic_and;

		default:
			assert(false);
			break;
	}
}

static bool ilbi_compare(il_factor_binary_op* self) {
	ilbinary_op_type t = self->type;
	switch (t) {
		case ilbinary_eq:
		case ilbinary_noteq:
		case ilbinary_gt:
		case ilbinary_ge:
		case ilbinary_lt:
		case ilbinary_le:
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