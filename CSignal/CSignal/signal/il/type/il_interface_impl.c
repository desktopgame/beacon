#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"

il_type * il_type_wrap_interface(il_interface * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_interface;
	ret->u.interface_ = ret;
	return ret;
}

il_interface * il_interface_new(const char * name) {
	il_interface* ret = (il_interface*)MEM_MALLOC(sizeof(il_interface));
	ret->method_list = vector_new();
	ret->name = text_strdup(name);
	return ret;
}

void il_interface_dump(il_interface * self) {
}

void il_interface_delete(il_interface * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}
