#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"

//proto
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache);
static void il_factor_invoke_bound_args_delete(vector_item item);

il_factor_invoke_bound* il_factor_invoke_bound_new(const char* name) {
	il_factor_invoke_bound* ret = (il_factor_invoke_bound*)MEM_MALLOC(sizeof(il_factor_invoke_bound));
	ret->name = text_strdup(name);
	ret->args = NULL;
	ret->type_args = NULL;
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, il_load_cache* cache) {
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cache);
	}
	if(modifier_is_static(self->m->modifier)) {
		opcode_buf_add(env->buf, (vector_item)op_invokestatic);
		opcode_buf_add(env->buf,(vector_item) self->index);
	} else {
		opcode_buf_add(env->buf,(vector_item) op_this);
		if(self->m->access == access_private) {
			opcode_buf_add(env->buf, (vector_item)op_invokespecial);
			opcode_buf_add(env->buf, (vector_item)self->index);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
			opcode_buf_add(env->buf, (vector_item)self->index);
		}
	}
}

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {
	vector_push(cache->type_args_vec, self->type_args);
	il_factor_invoke_bound_check(self, env, cache);
	vector_pop(cache->type_args_vec);
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache) {
	type* tp = (type*)vector_top(cache->type_vec);
	il_factor_invoke_bound_check(self, env, cache);
	if(self->m->return_vtype.tag == virtualtype_default) {
		return self->m->return_vtype.u.gtype;
	} else if(self->m->return_vtype.tag == virtualtype_class_tv) {
		//ここで新しいジェネリックタイプを作る
		if(self->resolved == NULL) {
			self->resolved = generic_type_new(NULL);
			self->resolved->virtual_type_index = self->m->return_vtype.u.index;
			self->resolved->tag = generic_type_tag_class;
		}
	} else if(self->m->return_vtype.tag == virtualtype_method_tv) {
		//ここで新しいジェネリックタイプを作る
		if(self->resolved == NULL) {
			self->resolved = generic_type_new(NULL);
			self->resolved->virtual_type_index = self->m->return_vtype.u.index;
			self->resolved->tag = generic_type_tag_method;
		}
	}
	return self->resolved;
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {
	vector_delete(self->args, il_factor_invoke_bound_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, il_load_cache* cache) {
	type* ctype = (type*)vector_top(cache->type_vec);
	int temp = -1;
	self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, cache, &temp);
	self->index = temp;
	assert(temp != -1);
}
static void il_factor_invoke_bound_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}