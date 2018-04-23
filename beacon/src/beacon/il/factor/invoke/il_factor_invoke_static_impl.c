#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../il_context.h"
#include "../../il_type_argument.h"
#include "../../../util/xassert.h"
#include "../../../util/vector.h"

//proto
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env, il_context* ilctx);
static void resolve_default(il_factor_invoke_static * self, enviroment * env, il_context* ilctx);
static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, il_context* ilctx);
static void il_factor_invoke_static_args_delete(vector_item item);
static void il_factor_invoke_static_typeargs_delete(vector_item item);

il_factor_invoke_static* il_factor_invoke_static_new(const char* name) {
	il_factor_invoke_static* ret = (il_factor_invoke_static*)MEM_MALLOC(sizeof(il_factor_invoke_static));
	ret->args = NULL;
	ret->fqcn = NULL;
	ret->type_args = NULL;
	ret->name = text_strdup(name);
	ret->m = NULL;
	ret->index = -1;
	ret->resolved = NULL;
	return ret;
}

void il_factor_invoke_static_generate(il_factor_invoke_static* self, enviroment* env, il_context* ilctx) {
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor_generate(e->factor, env, ilctx);
		if(il_error_panic()) {
			return;
		}
	}
	opcode_buf_add(env->buf, (vector_item)op_invokestatic);
	opcode_buf_add(env->buf, (vector_item)self->m->parent->absolute_index);
	opcode_buf_add(env->buf, (vector_item)self->index);
}

void il_factor_invoke_static_load(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	vector_push(ilctx->type_args_vec, self->type_args);
	il_factor_invoke_static_check(self, env, ilctx);
	vector_pop(ilctx->type_args_vec);
}

generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	il_factor_invoke_static_check(self, env, ilctx);
	//メソッドを解決できなかった場合
	if(il_error_panic()) {
		return NULL;
	}
	virtual_type returnvType = self->m->return_vtype;
	if(returnvType.tag != virtualtype_default) {
		resolve_non_default(self, env, ilctx);
		return self->resolved;
	} else {
		resolve_default(self, env, ilctx);
		return self->resolved;
	}
}

void il_factor_invoke_static_delete(il_factor_invoke_static* self) {
	vector_delete(self->args, il_factor_invoke_static_args_delete);
	vector_delete(self->type_args, il_factor_invoke_static_typeargs_delete);
	fqcn_cache_delete(self->fqcn);
//	generic_type_delete(self->resolved);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
//FIXME:il_factor_invokeからのコピペ
static void resolve_non_default(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	if(self->resolved != NULL) {
		return;
	}
	virtual_type returnvType = self->m->return_vtype;
	generic_type* instanced_type = (generic_type*)vector_at(self->type_args, returnvType.u.index);
	self->resolved = generic_type_make(instanced_type->core_type);
	self->resolved->tag = generic_type_tag_method;
	self->resolved->virtual_type_index = returnvType.u.index;
}

static void resolve_default(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	if(self->resolved != NULL) {
		return;
	}
	virtual_type returnvType = self->m->return_vtype;
	vector_push(ilctx->type_args_vec, self->type_args);
	self->resolved = generic_type_apply(returnvType.u.gtype, ilctx);
	vector_pop(ilctx->type_args_vec);
}

static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	class_* cls = il_context_class(ilctx, self->fqcn);
	int temp = -1;
//	XSTREQ(self->name, "write");
	il_type_argument_resolve(self->type_args, ilctx);
	vector_push(ilctx->type_args_vec, self->type_args);
	self->m = class_find_smethod(cls, self->name, self->args, env, ilctx, &temp);
	self->index = temp;
	//メソッドが見つからない
	if(temp == -1) {
		il_error_report(ilerror_undefined_method, self->name);
	}
	vector_pop(ilctx->type_args_vec);
}

static void il_factor_invoke_static_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_static_typeargs_delete(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}