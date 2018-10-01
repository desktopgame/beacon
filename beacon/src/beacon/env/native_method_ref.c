#include "native_method_ref.h"
#include <stdlib.h>
#include "../util/mem.h"

native_method_ref * NewNativeMethodRef(native_impl impl) {
	native_method_ref* ret = (native_method_ref*)MEM_MALLOC(sizeof(native_method_ref));
	ret->impl = impl;
	return ret;
}

void DeleteNativeMethodRef(native_method_ref * self) {
	MEM_FREE(self);
}
