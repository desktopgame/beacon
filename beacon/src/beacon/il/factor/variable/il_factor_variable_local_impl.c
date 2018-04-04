#include "il_factor_variable_local_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/xassert.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_impl.h"
#include "../../../env/field.h"
#include "../../../vm/enviroment.h"
#include "../../../vm/symbol_entry.h"

il_factor_variable_local* il_factor_variable_local_new(const char* name) {
	il_factor_variable_local* ret = (il_factor_variable_local*)MEM_MALLOC(sizeof(il_factor_variable_local));
	ret->name = text_strdup(name);
	ret->type = variable_local_undefined;
	ret->type_args = NULL;
	ret->gt = NULL;
	return ret;
}

void il_factor_variable_local_generate(il_factor_variable_local* self, enviroment* env, il_load_cache* cache) {
	assert(self->type != variable_local_undefined);
	if(self->type == variable_local_scope) {
		opcode_buf_add(env->buf, (vector_item)op_load);
		opcode_buf_add(env->buf, (vector_item)self->u.entry_->index);
	} else if(self->type == variable_local_field) {
		opcode_buf_add(env->buf, (vector_item)op_get_field);
		opcode_buf_add(env->buf, self->u.field_index);
	}
}

void il_factor_variable_local_load(il_factor_variable_local * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {
	if(self->type == variable_local_undefined) {
		//XSTREQ(self->name, "iter");
		//NOTE:変数宣言の後にその変数を使用する場合、
		//factorはload時点でシンボルエントリーを取得しようとするが、
		//stmtはgenerate時点でシンボルテーブルへ書き込むので、
		//NULLになることがある。
		self->type = variable_local_scope;
		symbol_entry* ent = symbol_table_entry(env->sym_table, NULL, self->name);
		if(ent == NULL) {
			self->type = variable_local_field;
			type* tp = (type*)vector_top(cache->type_vec);
			int temp = -1;
			field* f = class_find_field(TYPE2CLASS(tp), self->name, &temp);
			self->u.field_index = temp;
			self->type = variable_local_field;
			assert(temp != -1);
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
			if(ent->gtype->type_args_list->length > 0) {
				generic_type* a = (generic_type*)vector_at(ent->gtype->type_args_list, 0);
				int x = 0;
			}
		}
	}
}

generic_type* il_factor_variable_local_eval(il_factor_variable_local * self, enviroment * env, il_load_cache* cache) {
	il_factor_variable_local_load(self, env, cache, NULL);
	assert(self->type != variable_local_undefined);
	return self->gt;
}

void il_factor_variable_local_delete(il_factor_variable_local* self) {
	vector_delete(self->type_args, vector_deleter_null);
	MEM_FREE(self->name);
	MEM_FREE(self);
}