#include "native_method_ref.h"
#include <stdlib.h>
#include "../util/mem.h"

NativeMethodRef * NewNativeMethodRef(NativeImpl impl) {
	NativeMethodRef* ret = (NativeMethodRef*)MEM_MALLOC(sizeof(NativeMethodRef));
	ret->Body = impl;
	return ret;
}

void DeleteNativeMethodRef(NativeMethodRef * self) {
	MEM_FREE(self);
}
