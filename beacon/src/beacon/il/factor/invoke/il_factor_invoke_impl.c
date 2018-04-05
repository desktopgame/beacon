#include "il_factor_invoke_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/xassert.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../env/method.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_factor_impl.h"

//proto
static void il_factor_invoke_args_delete(vector_item item);
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, il_context* ilctx);

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

void il_factor_invoke_generate(il_factor_invoke* self, enviroment* env, il_context* ilctx) {
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, ilctx);
	}
	if(self->m->parent->tag == type_interface) {
		opcode_buf_add(env->buf, (vector_item)op_invokeinterface);
		opcode_buf_add(env->buf, (vector_item)self->m->parent->absolute_index);
		opcode_buf_add(env->buf, (vector_item)self->index);
	} else {
		opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
		opcode_buf_add(env->buf, (vector_item)self->index);
	}
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, il_context* ilctx, il_ehandler* eh) {
	vector_push(ilctx->type_args_vec, self->type_args);
	vector_push(ilctx->receiver_vec, il_factor_eval(self->receiver, env, ilctx));

	il_factor_load(self->receiver, env, ilctx, eh);
	il_factor_invoke_check(self, env, ilctx);

	vector_pop(ilctx->receiver_vec);
	vector_pop(ilctx->type_args_vec);
}

generic_type* il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, il_context* ilctx) {
	il_factor_invoke_check(self, env, ilctx);
	generic_type* receivergType = il_factor_eval(self->receiver, env, ilctx);
	//T自体ではなく、返すかたにTが含まれる場合
	virtual_type returnvType = self->m->return_vtype;
	if(self->receiver->type == ilfactor_member_op) {
		il_factor_member_op* ilmem = IL_FACT2MEM(self->receiver);
		//XSTREQ(ilmem->name, "stackTrace");
	}
	if(returnvType.tag != virtualtype_default) {
		if(self->resolved == NULL) {
			self->resolved = generic_type_new(NULL);
			self->resolved->tag = generic_type_tag_class;
			generic_type* a = (generic_type*)vector_at(receivergType->type_args_list, returnvType.u.index);
			self->resolved->core_type = a->core_type;
		}
		return self->resolved;
		//receiverをeval
		//virtual_type_indexを当てはめる。
		//new_instanceはevalでコンストラクタで与えられた実型引数を詰める。
	} else {
		generic_type* gt = returnvType.u.gtype;
		if(self->resolved == NULL) {
			vector_push(ilctx->receiver_vec, receivergType);
			self->resolved = generic_type_apply(gt, ilctx);
			vector_pop(ilctx->receiver_vec);
		}
		return self->resolved;
	}
}

void il_factor_invoke_delete(il_factor_invoke* self) {
	vector_delete(self->args, il_factor_invoke_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void il_factor_invoke_check(il_factor_invoke * self, enviroment * env, il_context* ilctx) {
	il_factor_load(self->receiver, env, ilctx, NULL);
	if(self->receiver->type == ilfactor_variable) {
		il_factor_variable* ilvar = IL_FACT2VAR(self->receiver);
		assert(ilvar->type != ilvariable_type_static);
	}
	//classではなく generic_type にメソッドを検索する関数
	generic_type* gtype = il_factor_eval(self->receiver, env, ilctx);
	type* ctype = gtype->core_type;
	int temp = -1;
	self->m = type_find_method(ctype, self->name, self->args, env, ilctx, &temp);
	//self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, cache, &temp);
	self->index = temp;
	assert(temp != -1);
}

static void il_factor_invoke_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}