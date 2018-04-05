#include "il_factor_invoke_static_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../env/type/class_impl.h"
#include "../../../vm/enviroment.h"
#include "../../il_argument.h"
#include "../../../util/xassert.h"

//proto
static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, il_context* ilctx);
static void il_factor_invoke_static_args_delete(vector_item item);

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
	}
	opcode_buf_add(env->buf, (vector_item)op_invokestatic);
	opcode_buf_add(env->buf, (vector_item)self->m->parent->absolute_index);
	opcode_buf_add(env->buf, (vector_item)self->index);
}

void il_factor_invoke_static_load(il_factor_invoke_static * self, enviroment * env, il_context* ilctx, il_ehandler* eh) {
	vector_push(ilctx->type_args_vec, self->type_args);
	il_factor_invoke_static_check(self, env, ilctx);
	vector_pop(ilctx->type_args_vec);
}

generic_type* il_factor_invoke_static_eval(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	il_factor_invoke_static_check(self, env, ilctx);
	virtual_type returnvType = self->m->return_vtype;
	if(returnvType.tag != virtualtype_default) {
		if(self->resolved == NULL) {
			self->resolved = generic_type_new(NULL);
			self->resolved->tag = generic_type_tag_method;
			self->resolved->virtual_type_index = returnvType.u.index;
		}
		return self->resolved;
	} else {
		return returnvType.u.gtype;
	}
}

void il_factor_invoke_static_delete(il_factor_invoke_static* self) {
	vector_delete(self->args, il_factor_invoke_static_args_delete);
	vector_delete(self->type_args, vector_deleter_null);
	fqcn_cache_delete(self->fqcn);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void il_factor_invoke_static_check(il_factor_invoke_static * self, enviroment * env, il_context* ilctx) {
	class_* cls = il_context_class(ilctx, self->fqcn);
	int temp = -1;
	for(int i=0; i<self->args->length; i++) {
		il_argument* e = (il_argument*)vector_at(self->args, i);
		il_factor* f = e->factor;
		//XSTREQ(self->name, "writeLine");
		//int a = 0;
	}
	self->m = class_find_smethod(cls, self->name, self->args, env, ilctx, &temp);
	self->index = temp;
	assert(temp != -1);
}

static void il_factor_invoke_static_args_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}