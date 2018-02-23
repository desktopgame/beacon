#include "generic_cache.h"
#include "../util/mem.h"

//proto
static void generic_cache_tree_delete(vector_item item);

generic_cache * generic_cache_new() {
	generic_cache* ret = (generic_cache*)MEM_MALLOC(sizeof(generic_cache));
	ret->fqcn = fqcn_cache_new();
	ret->type_args = vector_new();
	return ret;
}

void generic_cache_delete(generic_cache * self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, generic_cache_tree_delete);
	MEM_FREE(self);
}
//private
static void generic_cache_tree_delete(vector_item item) {
	generic_cache* e = (generic_cache*)item;
	generic_cache_delete(e);
}