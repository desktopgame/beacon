#include "il_load_cache.h"
#include "../util/mem.h"
#include "../env/type_impl.h"
#include "../env/namespace.h"
#include "../env/fqcn_cache.h"


il_load_cache * il_load_cache_new() {
	il_load_cache* ret = (il_load_cache*)MEM_MALLOC(sizeof(il_load_cache));
	ret->namespace_vec = vector_new();
	ret->type_vec = vector_new();
	ret->method_vec = vector_new();
	ret->while_start_vec = vector_new();
	ret->while_end_vec = vector_new();
	ret->toplevel = false;
	ret->receiver_vec = vector_new();
	ret->type_args_vec = vector_new();
	return ret;
}

namespace_* il_load_cache_namespace(il_load_cache* self) {
	namespace_* ret = (namespace_*)vector_top(self->namespace_vec);
	if(ret == NULL) {
		ret = namespace_lang();
	}
	return ret;
}

class_ * il_load_cache_class(il_load_cache * self, fqcn_cache* fqcn) {
	vector_item e = vector_top(self->namespace_vec);
	class_* tp = NULL;
	if (e != NULL) {
		namespace_* scope = (namespace_*)e;
		tp = fqcn_class(fqcn, scope);
	} else {
		tp = fqcn_class(fqcn, NULL);
	}
	return tp;
}

void il_load_cache_delete(il_load_cache * self) {
	vector_delete(self->namespace_vec, vector_deleter_null);
	vector_delete(self->type_vec, vector_deleter_null);
	vector_delete(self->method_vec, vector_deleter_null);
	vector_delete(self->while_start_vec, vector_deleter_null);
	vector_delete(self->while_end_vec, vector_deleter_null);
	vector_delete(self->receiver_vec, vector_deleter_null);
	vector_delete(self->type_args_vec, vector_deleter_null);
	MEM_FREE(self);
}
