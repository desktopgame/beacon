#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"
#include "../env/method.h"
#include "../env/type_interface.h"
#include "../env/type_impl.h"
#include "../env/generic_type.h"
#include "../env/fqcn_cache.h"

call_context* call_context_malloc(call_context_tag tag, const char* filename, int lineno) {
	call_context* ret = mem_malloc(sizeof(call_context), filename, lineno);
	control_structure cs = {};
	ret->call_stack = vector_malloc(filename, lineno);
	ret->space = NULL;
	ret->ty = NULL;
	ret->tag = tag;
	ret->control = cs;
	control_structure_alloc(&ret->control);
	return ret;
}

call_frame* call_context_push(call_context* self, call_frame_tag tag) {
	call_frame* fr = MEM_MALLOC(sizeof(call_frame));
	fr->tag = tag;
	vector_push(self->call_stack, fr);
	return fr;
}

call_frame* call_context_top(call_context* self) {
	return vector_top(self->call_stack);
}

void call_context_pop(call_context* self) {
	call_frame* fr = vector_pop(self->call_stack);
	call_frame_delete(fr);
}

namespace_* call_context_namespace(call_context* self) {
	if(self->space != NULL) {
		return self->space;
	}
	return namespace_lang();
}

method* call_context_method(call_context* self) {
	if(self->tag != call_method_T) {
		return NULL;
	}
	return self->u.mt;
}

type* call_context_type(call_context* self) {
	if(self->tag == call_top_T) {
		return namespace_get_type(namespace_lang(), string_pool_intern("World"));
	}
	return self->ty;
}

class_* call_context_class(call_context* self) {
	return TYPE2CLASS(call_context_type(self));
}

generic_type* call_context_receiver(call_context* self) {
	call_frame* cfr = vector_top(self->call_stack);
	if(cfr->tag == call_instance_invoke_T) {
		return cfr->u.instance_invoke.receiver;
	} else if(cfr->tag == call_self_invoke_T) {
		return NULL;
	} else if(cfr->tag == call_ctor_call_T) {
		return cfr->u.ctor_call.self;
	}
	return NULL;
}

type* call_context_eval_type(call_context* self, fqcn_cache* fqcn) {
	type* tp = fqcn_type(fqcn, self->space);
	if(tp == NULL) {
		tp = fqcn_type(fqcn, namespace_lang());
	}
	return tp;
}

vector* call_context_typeargs(call_context* self) {
	call_frame* cfr = vector_top(self->call_stack);
	if(cfr->tag == call_instance_invoke_T) {
		return cfr->u.instance_invoke.typeargs;
	} else if(cfr->tag == call_static_invoke_T) {
		return cfr->u.static_invoke.typeargs;
	} else if(cfr->tag == call_self_invoke_T) {
		return cfr->u.self_invoke.typeargs;
	}
	return NULL;
}

void call_context_delete(call_context* self) {
	MEM_FREE(self);
	control_structure_free(self->control);
	vector_delete(self->call_stack, vector_deleter_null);
}