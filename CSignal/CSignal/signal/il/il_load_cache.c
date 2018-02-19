#include "il_load_cache.h"
#include "../util/mem.h"

il_load_cache * il_load_cache_new() {
	il_load_cache* ret = (il_load_cache*)MEM_MALLOC(sizeof(il_load_cache));
	ret->namespace_vec = vector_new();
	ret->type_vec = vector_new();
	ret->while_start_vec = vector_new();
	ret->while_end_vec = vector_new();
	ret->toplevel = false;
	return ret;
}

void il_load_cache_delete(il_load_cache * self) {
	vector_delete(self->namespace_vec, vector_deleter_null);
	vector_delete(self->type_vec, vector_deleter_null);
	vector_delete(self->while_start_vec, vector_deleter_null);
	vector_delete(self->while_end_vec, vector_deleter_null);
	MEM_FREE(self);
}
