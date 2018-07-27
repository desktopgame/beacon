#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_impl.h"
#include "../../../env/field.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/symbol_entry.h"
#include "../../il_argument.h"
#include <string.h>
#include <stdio.h>

il_factor_variable_local* il_factor_variable_local_new(string_view namev) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->namev = namev;
	ret->type = variable_local_undefined;
	ret->type_args = NULL;
	ret->gt = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env) {
	il_factor_variable_local_load(self, env);
	assert(self->type != variable_local_undefined);
	if(self->type == variable_local_scope) {
		opcode_buf_add(env->buf, (vector_item)op_load);
		opcode_buf_add(env->buf, (vector_item)self->u.entry_->index);
	} else if(self->type == variable_local_field) {
		opcode_buf_add(env->buf, (vector_item)op_this);
		opcode_buf_add(env->buf, (vector_item)op_get_field);
		opcode_buf_add(env->buf, (vector_item)self->u.field_index);
	}
}

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env) {
	if(self->type == variable_local_undefined) {
		//NOTE:変数宣言の後にその変数を使用する場合、
		//factorはload時点でシンボルエントリーを取得しようとするが、
		//stmtはgenerate時点でシンボルテーブルへ書き込むので、
		//NULLになることがある。
		self->type = variable_local_scope;
		symbol_entry* ent = symbol_table_entry(env->sym_table, NULL, self->namev);
		//ローカル変数として解決出来なかったので、
		//フィールドとして解決する
		if(ent == NULL) {
			//対応するフィールドを検索
			self->type = variable_local_field;
			//NOTE:トップレベルではここが空なので、
			//定義されていない変数とみなせる？
			type* tp = cctop_type();
			if(tp->tag == type_interface/* この条件は構文規則からして満たさないはず */) {
				il_error_report(ilerror_undefined_variable, string_pool_ref2str(self->namev));
				return;
			}
			int temp = -1;
			field* f = class_find_field(TYPE2CLASS(tp), self->namev, &temp);
			self->u.field_index = temp;
			self->type = variable_local_field;
			if(temp == -1) {
				il_error_report(ilerror_undefined_field, string_pool_ref2str(self->namev));
				return;
			}
			//フィールドの型を調べる
			generic_type* gt = f->gtype;
			//virtual_type vt = f->vtype;
			if(gt->tag == generic_type_tag_none) {
				self->gt = gt;
			} else if(gt->tag == generic_type_tag_class) {
				self->gt = generic_type_new(NULL);
				self->gt->tag = generic_type_tag_class;
				self->gt->virtual_type_index = gt->virtual_type_index;
			} else if(gt->tag == generic_type_tag_method) {
				self->gt = generic_type_new(NULL);
				self->gt->tag = generic_type_tag_method;
				self->gt->virtual_type_index = gt->virtual_type_index;
			}
		} else {
			self->u.entry_ = ent;
			self->gt = ent->gtype;
		}
	}
}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env) {
	il_factor_variable_local_load(self, env);
	assert(self->type != variable_local_undefined);
	return self->gt;
}

char* il_factor_variable_local_tostr(il_factor_variable_local * self, enviroment * env) {
	return text_strdup(string_pool_ref2str(self->namev));
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	vector_delete(self->type_args, vector_deleter_null);
//	generic_type_delete(self->gt);
	MEM_FREE(self);
}