#include "il_factor_invoke_bound_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/xassert.h"
#include "../../../env/generic_type.h"
#include "../../../env/type_interface.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_type_argument.h"

//proto
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx);
static void resolve_default(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx);
static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx);
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

void il_factor_invoke_bound_generate(il_factor_invoke_bound* self, enviroment* env, il_context* ilctx) {
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, ilctx);
		if(il_error_panic()) {
			return;
		}
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

void il_factor_invoke_bound_load(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx, il_ehandler* eh) {
	vector_push(ilctx->type_args_vec, self->type_args);
	il_factor_invoke_bound_check(self, env, ilctx);
	vector_pop(ilctx->type_args_vec);
}

generic_type* il_factor_invoke_bound_eval(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx) {
	type* tp = (type*)vector_top(ilctx->type_vec);
	//メソッドが見つからない
	il_factor_invoke_bound_check(self, env, ilctx);
	if(il_error_panic()) {
		return NULL;
	}
	if(self->m->return_vtype.tag != virtualtype_default) {
		resolve_non_default(self, env, ilctx);
		return self->resolved;
	} else {
		resolve_default(self, env, ilctx);
		return self->resolved;
	}
	return self->resolved;
}

void il_factor_invoke_bound_delete(il_factor_invoke_bound* self) {
	vector_delete(self->args, il_factor_invoke_bound_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	//generic_type_delete(self->resolved);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx) {
	if(self->resolved != NULL) {
		return;
	}
	type* tp = (type*)vector_top(ilctx->type_vec);
//	generic_type* receivergType = tp->generic_self;
	virtual_type returnvType = self->m->return_vtype;
	if(returnvType.tag == virtualtype_class_tv) {
		self->resolved = generic_type_make(NULL);
		self->resolved->tag = generic_type_tag_class;
		self->resolved->virtual_type_index = returnvType.u.index;
	} else if(returnvType.tag == virtualtype_method_tv) {
		//メソッドに渡された型引数を参照する
		generic_type* instanced_type = (generic_type*)vector_at(self->type_args, returnvType.u.index);
		self->resolved = generic_type_make(instanced_type->core_type);
		self->resolved->tag = generic_type_tag_class;
	}
}

static void resolve_default(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx) {
	if(self->resolved != NULL) {
		return;
	}
	virtual_type returnvType = self->m->return_vtype;
	vector_push(ilctx->type_args_vec, self->type_args);
	self->resolved = generic_type_apply(returnvType.u.gtype, ilctx);
	vector_pop(ilctx->type_args_vec);
}

static void il_factor_invoke_bound_check(il_factor_invoke_bound * self, enviroment * env, il_context* ilctx) {
	if(self->index != -1) {
		return;
	}
	//対応するメソッドを検索
	type* ctype = (type*)vector_top(ilctx->type_vec);
	int temp = -1;
	il_type_argument_resolve(self->type_args, ilctx);
	vector_push(ilctx->receiver_vec, ctype->generic_self);
	vector_push(ilctx->type_args_vec, self->type_args);
	self->m = class_find_method(TYPE2CLASS(ctype), self->name, self->args, env, ilctx, &temp);
	self->index = temp;
	vector_pop(ilctx->receiver_vec);
	vector_pop(ilctx->type_args_vec);
	if(temp == -1) {
		il_error_report(ilerror_undefined_method, self->name);
	}
}
static void il_factor_invoke_bound_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}