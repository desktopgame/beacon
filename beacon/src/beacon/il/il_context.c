#include "il_context.h"
#include "../util/mem.h"
#include "../env/type_impl.h"
#include "../env/namespace.h"
#include "../env/fqcn_cache.h"


il_context * il_context_new() {
	il_context* ret = (il_context*)MEM_MALLOC(sizeof(il_context));
	ret->namespace_vec = vector_new();
	ret->type_vec = vector_new();
	ret->method_vec = vector_new();
	ret->ctor_vec = vector_new();
	ret->while_start_vec = vector_new();
	ret->while_end_vec = vector_new();
	ret->toplevel = false;
	ret->receiver_vec = vector_new();
	ret->type_args_vec = vector_new();
	ret->find_instance = 0;
	ret->find_static = 0;
	return ret;
}

namespace_* il_context_namespace(il_context* self) {
	namespace_* ret = (namespace_*)vector_top(self->namespace_vec);
	if(ret == NULL) {
		ret = namespace_lang();
	}
	return ret;
}

class_ * il_context_class(il_context * self, fqcn_cache* fqcn) {
	vector_item e = vector_top(self->namespace_vec);
	class_* tp = NULL;
	if (e != NULL) {
		namespace_* scope = (namespace_*)e;
		tp = fqcn_class(fqcn, scope);
	} else {
		tp = fqcn_class(fqcn, NULL);
	}
	if(tp == NULL) {
		tp = fqcn_class(fqcn, namespace_lang());
	}
	return tp;
}

void il_context_delete(il_context * self) {
	vector_delete(self->namespace_vec, vector_deleter_null);
	vector_delete(self->type_vec, vector_deleter_null);
	vector_delete(self->method_vec, vector_deleter_null);
	vector_delete(self->while_start_vec, vector_deleter_null);
	vector_delete(self->while_end_vec, vector_deleter_null);
	vector_delete(self->receiver_vec, vector_deleter_null);
	vector_delete(self->type_args_vec, vector_deleter_null);
	vector_delete(self->ctor_vec, vector_deleter_null);
	MEM_FREE(self);
}
