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

typedef enum bi_operator_t {
	bi_add,
	bi_sub,
	bi_mul,
	bi_div,
	bi_mod,

	bi_bit_or,
	bi_logic_or,

	bi_bit_and,
	bi_logic_and,

	bi_eq,
	bi_noteq,
	bi_gt,
	bi_ge,
	bi_lt,
	bi_le
} bi_operator_t;

//proto
static char* il_factor_binary_op_optostr(il_factor_binary_op* self);
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_context* ilctx, bi_operator_t c);
static opcode bi_operator_to_opi(bi_operator_t bi);
static opcode bi_operator_to_opd(bi_operator_t bi);
static opcode bi_operator_to_opb(bi_operator_t bi);
static bool ilbi_compare(il_factor_binary_op* self);
static void assign_dump_operator(il_factor_binary_op* self);

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
	assign_dump_operator(self);
	text_putline();
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env, il_context* ilctx) {
	switch (self->type) {
		case ilbinary_add:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_add);
			break;
		case ilbinary_sub:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_sub);
			break;
		case ilbinary_mul:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_mul);
			break;
		case ilbinary_div:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_div);
			break;
		case ilbinary_mod:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_mod);
			break;


		case ilbinary_bit_or:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_bit_or);
			break;
		case ilbinary_logic_or:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_logic_or);
			break;


		case ilbinary_bit_and:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_bit_and);
			break;
		case ilbinary_logic_and:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_logic_and);
			break;

		case ilbinary_eq:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_eq);
			break;
		case ilbinary_noteq:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_noteq);
			break;
		case ilbinary_gt:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_gt);
			break;
		case ilbinary_ge:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_ge);
			break;
		case ilbinary_lt:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_lt);
			break;
		case ilbinary_le:
			il_factor_binary_op_generate_impl(self, env, ilctx, bi_le);
			break;
		default:
			break;
	}
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
		default: return "NULL";
	}
}

static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_context* ilctx, bi_operator_t c) {
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

static opcode bi_operator_to_opi(bi_operator_t bi) {
	switch (bi) {
		case bi_add: return op_iadd;
		case bi_sub: return op_isub;
		case bi_mul: return op_imul;
		case bi_div: return op_idiv;
		case bi_mod: return op_imod;

		case bi_bit_or: return op_ibit_or;
		case bi_logic_or: return op_ilogic_or;
		case bi_bit_and: return op_ibit_and;
		case bi_logic_and: return op_ilogic_and;

		case bi_eq: return op_ieq;
		case bi_noteq: return op_inoteq;
		case bi_gt: return op_igt;
		case bi_ge: return op_ige;
		case bi_lt: return op_ilt;
		case bi_le: return op_ile;

		default:
			break;
	}
}

static opcode bi_operator_to_opd(bi_operator_t bi) {
	//return op_dbit_and - bi;
	//*
	switch (bi) {
		case bi_add: return op_dadd;
		case bi_sub: return op_dsub;
		case bi_mul: return op_dmul;
		case bi_div: return op_ddiv;
		case bi_mod: return op_dmod;

		case bi_bit_or:
		case bi_logic_or:
		case bi_bit_and:
		case bi_logic_and:
			//未対応
			assert(false);
			break;

		case bi_eq: return op_deq;
		case bi_noteq: return op_dnoteq;
		case bi_gt: return op_dgt;
		case bi_ge: return op_dge;
		case bi_lt: return op_dlt;
		case bi_le: return op_dle;

		default:
			break;
	}
	//*/
}

static opcode bi_operator_to_opb(bi_operator_t bi) {
	switch (bi) {
		case bi_bit_or: return op_bbit_or;
		case bi_logic_or: return op_blogic_or;
		case bi_bit_and: return op_bbit_and;
		case bi_logic_and: return op_blogic_and;

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

static void assign_dump_operator(il_factor_binary_op* self) {
	switch (self->type) {
		case ilbinary_add:
			text_printf("+");
			break;
		case ilbinary_sub:
			text_printf("-");
			break;
		case ilbinary_mul:
			text_printf("*");
			break;
		case ilbinary_div:
			text_printf("/");
			break;
		case ilbinary_mod:
			text_printf("%");
			break;


		case ilbinary_bit_or:
			text_printf("|");
			break;
		case ilbinary_logic_or:
			text_printf("||");
			break;


		case ilbinary_bit_and:
			text_printf("&");
			break;
		case ilbinary_logic_and:
			text_printf("&&");
			break;

		case ilbinary_eq:
			text_printf("==");
			break;
		case ilbinary_noteq:
			text_printf("!=");
			break;
		case ilbinary_gt:
			text_printf(">");
			break;
		case ilbinary_ge:
			text_printf(">=");
			break;
		case ilbinary_lt:
			text_printf("<");
			break;
		case ilbinary_le:
			text_printf("<=");
			break;
		default:
			break;
	}
}

il_factor_binary_op* il_factor_cast_binary_op(il_factor* fact) {
	assert(fact->type == ilfactor_binary_op);
	return fact->u.binary_;
}