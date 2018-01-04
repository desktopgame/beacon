#include "il_factor_binary_op_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../../util/text.h"
#include "il_factor_variable_impl.h"
#include "il_factor_field_access_impl.h"
#include "../../env/class.h"
#include "../../vm/enviroment.h"
#include "../../util/mem.h"

//proto
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, opcode c);

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
	switch (self->type) {
		case ilbinary_add:
			printf("+");
			break;
		case ilbinary_sub:
			printf("-");
			break;
		case ilbinary_mul:
			printf("*");
			break;
		case ilbinary_div:
			printf("/");
			break;
		case ilbinary_mod:
			printf("%");
			break;


		case ilbinary_bit_or:
			printf("|");
			break;
		case ilbinary_logic_or:
			printf("||");
			break;


		case ilbinary_bit_and:
			printf("&");
			break;
		case ilbinary_logic_and:
			printf("&&");
			break;

		case ilbinary_eq:
			printf("==");
			break;
		case ilbinary_noteq:
			printf("!=");
			break;
		case ilbinary_gt:
			printf(">");
			break;
		case ilbinary_ge:
			printf(">=");
			break;
		case ilbinary_lt:
			printf("<");
			break;
		case ilbinary_le:
			printf("<=");
			break;

		case ilbinary_assign:
			printf("=");
			break;
		case ilbinary_add_assign:
			printf("+=");
			break;
		case ilbinary_sub_assign:
			printf("-=");
			break;
		case ilbinary_mul_assign:
			printf("*=");
			break;
		case ilbinary_div_assign:
			printf("/=");
			break;
		case ilbinary_mod_assign:
			printf("%=");
			break;
		default:
			break;
	}
	text_putline();
	il_factor_dump(self->left, depth + 1);
	il_factor_dump(self->right, depth + 1);
}

void il_factor_binary_op_generate(il_factor_binary_op * self, enviroment* env) {
	
	switch (self->type) {
		case ilbinary_add:
			il_factor_binary_op_generate_impl(self, env, op_add);
			break;
		case ilbinary_sub:
			il_factor_binary_op_generate_impl(self, env, op_sub);
			break;
		case ilbinary_mul:
			il_factor_binary_op_generate_impl(self, env, op_mul);
			break;
		case ilbinary_div:
			il_factor_binary_op_generate_impl(self, env, op_div);
			break;
		case ilbinary_mod:
			il_factor_binary_op_generate_impl(self, env, op_mod);
			break;


		case ilbinary_bit_or:
			il_factor_binary_op_generate_impl(self, env, op_bit_or);
			break;
		case ilbinary_logic_or:
			il_factor_binary_op_generate_impl(self, env, op_logic_or);
			break;


		case ilbinary_bit_and:
			il_factor_binary_op_generate_impl(self, env, op_bit_and);
			break;
		case ilbinary_logic_and:
			il_factor_binary_op_generate_impl(self, env, op_logic_and);
			break;

		case ilbinary_eq:
			il_factor_binary_op_generate_impl(self, env, op_eq);
			break;
		case ilbinary_noteq:
			il_factor_binary_op_generate_impl(self, env, op_noteq);
			break;
		case ilbinary_gt:
			il_factor_binary_op_generate_impl(self, env, op_gt);
			break;
		case ilbinary_ge:
			il_factor_binary_op_generate_impl(self, env, op_ge);
			break;
		case ilbinary_lt:
			il_factor_binary_op_generate_impl(self, env, op_lt);
			break;
		case ilbinary_le:
			il_factor_binary_op_generate_impl(self, env, op_le);
			break;
		//フィールドへの代入(put)なら、
		//フィールドのインデックス
		//ローカル変数への代入(store)なら、
		//実引数を0として関数の頭からカウントしたインデックス
		case ilbinary_assign:
		{
			if (self->left->type == ilfactor_field_access) {
				il_factor_field_access* field_access = self->left->u.field_access_;
				il_factor_eval(self->left, env);
				il_factor_generate(field_access->fact, env);
				il_factor_generate(self->right, env);
				opcode_buf_add(env->buf, op_put_field);
				opcode_buf_add(env->buf, field_access->fieldIndex);
			} else {
				il_factor_generate(self->right, env);
				assert(self->left->type == ilfactor_variable);
				il_factor_variable* v = (il_factor_variable*)self->left;
				opcode_buf_add(env->buf, op_store);
				opcode_buf_add(env->buf, v->index);
			}
			break;
		}

		default:
			break;
	}
}

void il_factor_binary_op_load(il_factor_binary_op * self, enviroment * env, il_ehandler * eh) {
}

class_ * il_factor_binary_op_eval(il_factor_binary_op * self, enviroment * env) {
	return NULL;
}

void il_factor_binary_op_delete(il_factor_binary_op * self) {
	il_factor_delete(self->left);
	il_factor_delete(self->right);
	MEM_FREE(self);
}

//private
static void il_factor_binary_op_generate_impl(il_factor_binary_op * self, enviroment * env, opcode c) {
	il_factor_generate(self->left, env);
	il_factor_generate(self->right, env);
	opcode_buf_add(env->buf, (vector_item)c);
}