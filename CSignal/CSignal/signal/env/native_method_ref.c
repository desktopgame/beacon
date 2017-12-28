#include "native_method_ref.h"
#include <stdlib.h>

native_method_ref * native_method_ref_new(native_impl impl) {
	native_method_ref* ret = (native_method_ref*)malloc(sizeof(native_method_ref));
	ret->impl = impl;
	return ret;
}

void native_method_ref_delete(native_method_ref * self) {
	free(self);
}
