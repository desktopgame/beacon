#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/xassert.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_impl.h"
#include "../../../env/field.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/symbol_entry.h"
#include "../../il_argument.h"
#include <string.h>
#include <stdio.h>

il_factor_variable_local* il_factor_variable_local_new(const char* name) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->name = text_strdup(name);
	ret->type = variable_local_undefined;
	ret->type_args = NULL;
	ret->gt = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env, il_context* ilctx) {
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

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env, il_context* ilctx, il_ehandler* eh) {
	if(self->type == variable_local_undefined) {
		//NOTE:変数宣言の後にその変数を使用する場合、
		//factorはload時点でシンボルエントリーを取得しようとするが、
		//stmtはgenerate時点でシンボルテーブルへ書き込むので、
		//NULLになることがある。
		self->type = variable_local_scope;
		symbol_entry* ent = symbol_table_entry(env->sym_table, NULL, self->name);
		//ローカル変数として解決出来なかったので、
		//フィールドとして解決する
		if(ent == NULL) {
			//対応するフィールドを検索
			self->type = variable_local_field;
			type* tp = (type*)vector_top(ilctx->type_vec);
			int temp = -1;
			field* f = class_find_field(TYPE2CLASS(tp), self->name, &temp);
			self->u.field_index = temp;
			self->type = variable_local_field;
			if(temp == -1) {
				il_error_report(ilerror_undefined_field, self->name);
				return;
			}
			//フィールドの型を調べる
			virtual_type vt = f->vtype;
			if(vt.tag == virtualtype_default) {
				self->gt = vt.u.gtype;
			} else if(vt.tag == virtualtype_class_tv) {
				self->gt = generic_type_new(NULL);
				self->gt->tag = generic_type_tag_class;
				self->gt->virtual_type_index = vt.u.index;
			} else if(vt.tag == virtualtype_method_tv) {
				self->gt = generic_type_new(NULL);
				self->gt->tag = generic_type_tag_method;
				self->gt->virtual_type_index = vt.u.index;
			}
		} else {
			self->u.entry_ = ent;
			self->gt = ent->gtype;
		}
		self->gt->ref_count++;
	}
}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env, il_context* ilctx) {
	//XSTREQ(self->name, "iter");
	il_factor_variable_local_load(self, env, ilctx, NULL);
	if(!strcmp(self->name, "iter")) {
	//	text_printf("local: ");
	//	generic_type_print(self->gt);
	//	text_printf("\n");
	}
	assert(self->type != variable_local_undefined);
	generic_type_validate(self->gt);
	if(!strcmp(self->name, "viter")) {
	//	generic_type_print(self->gt);
	//	printf("\n");
	//	int a = 0;
	}
	return self->gt;
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	vector_delete(self->type_args, vector_deleter_null);
//	generic_type_delete(self->gt);
	MEM_FREE(self->name);
	MEM_FREE(self);
}