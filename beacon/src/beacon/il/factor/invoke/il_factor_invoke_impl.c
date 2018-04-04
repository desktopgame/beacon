#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/method.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_factor_impl.h"

//proto
static void il_factor_invoke_args_delete(vector_item item);
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, il_load_cache* cache);

il_factor_invoke* il_factor_invoke_new(const char* name) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->args = NULL;
	ret->receiver = NULL;
	ret->type_args = NULL;
	ret->index = -1;
	ret->m = NULL;
	ret->name = text_strdup(name);
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_generate(il_factor_invoke* self, enviroment* env, il_load_cache* cache) {
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, cache);
	}
	opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
	opcode_buf_add(env->buf, (vector_item)self->index);
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, il_load_cache* cache, il_ehandler* eh) {
	vector_push(cache->type_args_vec, self->type_args);
	vector_push(cache->receiver_vec, il_factor_eval(self->receiver, env, cache));

	il_factor_load(self->receiver, env, cache, eh);
	il_factor_invoke_check(self, env, cache);

	vector_pop(cache->receiver_vec);
	vector_pop(cache->type_args_vec);
}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_invoke_check(self, env, cache);
	virtual_type returnvType = self->m->return_vtype;
	if(returnvType.tag != virtualtype_default) {
		if(self->resolved == NULL) {
			generic_type* gt = il_factor_eval(self->receiver, env, cache);
			self->resolved = generic_type_new(NULL);
			if(returnvType.tag == virtualtype_class_tv) {
				self->resolved->tag = virtualtype_class_tv;
			} else if(returnvType.tag == virtualtype_method_tv) {
				self->resolved->tag = virtualtype_method_tv;
			}
			self->resolved->virtual_type_index = returnvType.u.index;
		}
		//receiverをeval
		//virtual_type_indexを当てはめる。
		//new_instanceはevalでコンストラクタで与えられた実型引数を詰める。
	} else {
		return returnvType.u.gtype;
	}
}

void il_factor_invoke_delete(il_factor_invoke* self) {
	vector_delete(self->args, il_factor_invoke_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_load(self->receiver, env, cache, NULL);
	if(self->receiver->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(self->receiver);
		assert(ilvar->type != ilvariable_type_static);
	}
	//classではなく generic_type にメソッドを検索する関数
	generic_type* gtype = il_factor_eval(self->receiver, env, cache);
	type* ctype = gtype->core_type;
	int temp = -1;
	self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, cache, &temp);
	self->index = temp;
	assert(temp != -1);
}

static void il_factor_invoke_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}