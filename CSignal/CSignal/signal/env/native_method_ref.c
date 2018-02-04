#include "native_method_ref.h"
#include <stdlib.h>
#include "../util/mem.h"

native_method_ref * native_method_ref_new(native_impl impl) {
	native_method_ref* ret = (native_method_ref*)MEM_MALLOC(sizeof(native_method_ref));
	ret->impl = impl;
	ret->ref_count = 0;
	return ret;
}

void native_method_ref_delete(native_method_ref * self) {
	if (self == NULL) {
		return;
	}
	self->ref_count--;
	if (self->ref_count <= 0) {
		MEM_FREE(self);
	}
}
