#include "generic_type.h"
#include "type_interface.h"
#include "../util/mem.h"

//proto
static void generic_type_tree_delete(vector_item item);

generic_type * generic_type_new(type * core_type) {
	generic_type* ret = (generic_type*)MEM_MALLOC(sizeof(generic_type));
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	return ret;
}

void generic_type_delete(generic_type * self) {
	vector_delete(self->type_args_list, generic_type_tree_delete);
	MEM_FREE(self);
}

//private
static void generic_type_tree_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}