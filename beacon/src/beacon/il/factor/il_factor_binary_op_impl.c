#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include "../../env/type_interface.h"
#include "../../env/field.h"
#include "../../env/namespace.h"
#include "../../vm/enviroment.h"
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
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_load_cache* cache, bi_operator_t c);
static opcode bi_operator_to_opi(bi_operator_t bi);
static opcode bi_operator_to_opd(bi_operator_t bi);
static opcode bi_operator_to_opb(bi_operator_t bi);
static bool ilbi_compare(il_factor_binary_op* self);
static void assign_dump_operator(il_factor_binary_op* self);
static void assign_generate_simple(il_factor_binary_op * self, enviroment* env, il_load_cache* cache);
static void assign_generate_start(il_factor_binary_op * self, enviroment* env, il_load_cache* cache);
static void assign_generate_end(il_factor_binary_op * self, enviroment* env, il_load_cache* cache);

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

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env, il_load_cache* cache) {
	switch (self->type) {
		case ilbinary_add:
			il_factor_binary_op_generate_impl(self, env, cache, bi_add);
			break;
		case ilbinary_sub:
			il_factor_binary_op_generate_impl(self, env, cache, bi_sub);
			break;
		case ilbinary_mul:
			il_factor_binary_op_generate_impl(self, env, cache, bi_mul);
			break;
		case ilbinary_div:
			il_factor_binary_op_generate_impl(self, env, cache, bi_div);
			break;
		case ilbinary_mod:
			il_factor_binary_op_generate_impl(self, env, cache, bi_mod);
			break;


		case ilbinary_bit_or:
			il_factor_binary_op_generate_impl(self, env, cache, bi_bit_or);
			break;
		case ilbinary_logic_or:
			il_factor_binary_op_generate_impl(self, env, cache, bi_logic_or);
			break;


		case ilbinary_bit_and:
			il_factor_binary_op_generate_impl(self, env, cache, bi_bit_and);
			break;
		case ilbinary_logic_and:
			il_factor_binary_op_generate_impl(self, env, cache, bi_logic_and);
			break;

		case ilbinary_eq:
			il_factor_binary_op_generate_impl(self, env, cache, bi_eq);
			break;
		case ilbinary_noteq:
			il_factor_binary_op_generate_impl(self, env, cache, bi_noteq);
			break;
		case ilbinary_gt:
			il_factor_binary_op_generate_impl(self, env, cache, bi_gt);
			break;
		case ilbinary_ge:
			il_factor_binary_op_generate_impl(self, env, cache, bi_ge);
			break;
		case ilbinary_lt:
			il_factor_binary_op_generate_impl(self, env, cache, bi_lt);
			break;
		case ilbinary_le:
			il_factor_binary_op_generate_impl(self, env, cache, bi_le);
			break;
		//フィールドへの代入(put)なら、
		//フィールドのインデックス
		//ローカル変数への代入(store)なら、
		//実引数を0として関数の頭からカウントしたインデックス
		case ilbinary_assign:
		{
			assign_generate_simple(self, env, cache);
			break;
		}

		case ilbinary_add_assign:
			assign_generate_start(self, env, cache);
			il_factor_binary_op_generate_impl(self, env, cache, bi_add);
			assign_generate_end(self, env, cache);
			break;

		case ilbinary_sub_assign:
			assign_generate_start(self, env, cache);
			il_factor_binary_op_generate_impl(self, env, cache, bi_sub);
			assign_generate_end(self, env, cache);
			break;

		case ilbinary_mul_assign:
			assign_generate_start(self, env, cache);
			il_factor_binary_op_generate_impl(self, env, cache, bi_mul);
			assign_generate_end(self, env, cache);
			break;

		case ilbinary_div_assign:
			assign_generate_start(self, env, cache);
			il_factor_binary_op_generate_impl(self, env, cache, bi_div);
			assign_generate_end(self, env, cache);
			break;

		case ilbinary_mod_assign:
			assign_generate_start(self, env, cache);
			il_factor_binary_op_generate_impl(self, env, cache, bi_mod);
			assign_generate_end(self, env, cache);
			break;
		default:
			break;
	}
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
	il_factor_load(self->left, env, cache, eh);
	il_factor_load(self->right, env, cache, eh);
}

generic_type* il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env, il_load_cache* cache) {
	generic_type* ltype = il_factor_eval(self->left, env, cache);
	generic_type* rtype = il_factor_eval(self->right, env, cache);
	if (ltype == CL_INT->generic_self &&
		rtype == CL_INT->generic_self) {
		if (ilbi_compare(self)) {
			return CL_BOOL->generic_self;
		}
		return CL_INT->generic_self;
	}
	if (ltype == CL_DOUBLE->generic_self &&
		rtype == CL_DOUBLE->generic_self) {
		if (ilbi_compare(self)) {
			return CL_BOOL->generic_self;
		}
		return CL_DOUBLE->generic_self;
	}
	if (ltype == CL_BOOL->generic_self &&
		rtype == CL_BOOL->generic_self) {
		return CL_BOOL->generic_self;
	}
	return NULL;
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}

//private
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, il_load_cache* cache, bi_operator_t c) {
	//ここで逆にしておく
	il_factor_generate(self->right, env, cache);
	il_factor_generate(self->left, env, cache);
	
	generic_type* ltype = (generic_type*)il_factor_eval(self->left, env, cache);
	generic_type* rtype = (generic_type*)il_factor_eval(self->right, env, cache);
	if (ltype == CL_INT->generic_self &&
		rtype == CL_INT->generic_self) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opi(c));
	}
	if (ltype == CL_DOUBLE->generic_self &&
		rtype == CL_DOUBLE->generic_self) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opd(c));
	}
	if (ltype == CL_BOOL->generic_self &&
		rtype == CL_BOOL->generic_self) {
		opcode_buf_add(env->buf, (vector_item)bi_operator_to_opb(c));
	}
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

		case ilbinary_assign:
			text_printf("=");
			break;
		case ilbinary_add_assign:
			text_printf("+=");
			break;
		case ilbinary_sub_assign:
			text_printf("-=");
			break;
		case ilbinary_mul_assign:
			text_printf("*=");
			break;
		case ilbinary_div_assign:
			text_printf("/=");
			break;
		case ilbinary_mod_assign:
			text_printf("%=");
			break;
		default:
			break;
	}
}

static void assign_generate_simple(il_factor_binary_op * self, enviroment* env, il_load_cache* cache) {
	/*
	if (self->left->type == ilfactor_static_field_access) {
		//NOTE:List<T>が定義されるとき、
		//static T foo;
		//のように型変数を静的領域に宣言することはできません。
		//右辺をプッシュ
		il_factor_static_field_access* sfa = self->left->u.static_field_access;
		type* lt = il_factor_eval(self->left, env, cache);
		il_factor_generate(self->right, env, cache);
		//フィールド型にルックアップ
		//opcode_buf_add(env->buf, op_lookup);
		//opcode_buf_add(env->buf, sfa->f->gtype->core_type->absolute_index);
		//プット
		opcode_buf_add(env->buf, op_put_static);
		opcode_buf_add(env->buf, sfa->f->gparent->core_type->absolute_index);
		opcode_buf_add(env->buf, sfa->field_index);
	} else if (self->left->type == ilfactor_field_access) {
		//右辺をプッシュ
		il_factor_field_access* field_access = self->left->u.field_access_;
		type* lt = il_factor_eval(self->left, env, cache);
		il_factor_generate(field_access->fact, env, cache);
		il_factor_generate(self->right, env, cache);
		assert(field_access->f->gtype != NULL &&
			   field_access->f->gtype->virtual_type_index == -1);
		//ルックアップ
		//opcode_buf_add(env->buf, op_lookup);
		//opcode_buf_add(env->buf, field_access->f->gtype->core_type->absolute_index);
		//プット
		if (modifier_is_static(field_access->f->modifier)) {
			opcode_buf_add(env->buf, op_put_static);
			opcode_buf_add(env->buf, field_access->f->gparent->core_type->absolute_index);
			opcode_buf_add(env->buf, field_access->field_index);
		} else {
			opcode_buf_add(env->buf, op_put_field);
			opcode_buf_add(env->buf, field_access->field_index);
		}
	} else {
		type* lt = il_factor_eval(self->left, env, cache);
		//右辺をプッシュ
		il_factor_generate(self->right, env, cache);
		//opcode_buf_add(env->buf, op_lookup);
		//左辺型にルックアップ
		//opcode_buf_add(env->buf, lt->absolute_index);
		//ストア
		assert(self->left->type == ilfactor_variable);
		il_factor_variable* v = self->left->u.variable_;
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, v->index);
	}
	*/
}

static void assign_generate_start(il_factor_binary_op * self, enviroment* env, il_load_cache* cache) {
	/*
	if (self->left->type == ilfactor_field_access) {
		il_factor_field_access* field_access = self->left->u.field_access_;
		il_factor_eval(self->left, env, cache);
		il_factor_generate(field_access->fact, env, cache);
	}
	*/
}

static void assign_generate_end(il_factor_binary_op * self, enviroment* env, il_load_cache* cache) {
	/*
	if (self->left->type == ilfactor_static_field_access) {
		il_factor_static_field_access* sfa = self->left->u.static_field_access;
		//代入先の静的フィールドの型でルックアップ
		//opcode_buf_add(env->buf, op_lookup);
		//opcode_buf_add(env->buf, sfa->f->gtype->core_type->absolute_index);
		//プット
		il_factor_eval(self->left, env, cache);
		//il_factor_generate(self->right, env);
		opcode_buf_add(env->buf, op_put_static);
		opcode_buf_add(env->buf, sfa->f->gparent->core_type->absolute_index);
		opcode_buf_add(env->buf, sfa->field_index);
	} else if (self->left->type == ilfactor_field_access) {
		il_factor_field_access* field_access = self->left->u.field_access_;
		if (modifier_is_static(field_access->f->modifier)) {
			//代入先の静的フィールドの型でルックアップ
			//opcode_buf_add(env->buf, op_lookup);
			//opcode_buf_add(env->buf, field_access->f->gtype->core_type->absolute_index);
			//プット
			opcode_buf_add(env->buf, op_put_static);
			opcode_buf_add(env->buf, field_access->f->gparent->core_type->absolute_index);
			opcode_buf_add(env->buf, field_access->field_index);
		} else {
			//代入先のフィールドの型でルックアップ
			//opcode_buf_add(env->buf, op_lookup);
			//opcode_buf_add(env->buf, field_access->f->gtype->core_type->absolute_index);
			//プット
			opcode_buf_add(env->buf, op_put_field);
			opcode_buf_add(env->buf, field_access->field_index);
		}
	} else {
		il_factor_eval(self->left, env, cache);
		//il_factor_generate(self->right, env);
		assert(self->left->type == ilfactor_variable);
		il_factor_variable* v = self->left->u.variable_;
		//代入先の変数の型でルックアップ
		//opcode_buf_add(env->buf, op_lookup);
		//opcode_buf_add(env->buf, il_factor_variable_eval(v, env, cache)->core_type->absolute_index);
		//ストア
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, v->index);
	}
	*/
}

il_factor_binary_op* il_factor_cast_binary_op(il_factor* fact) {
	assert(fact->type == ilfactor_binary_op);
	return fact->u.binary_;
}