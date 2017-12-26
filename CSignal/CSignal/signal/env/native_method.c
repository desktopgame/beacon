#include "native_method.h"
#include <stdlib.h>
#include "method.h"
#include "../vm/vm.h"

native_method * native_method_new() {
	native_method* ret = (native_method*)malloc(sizeof(native_method));
	ret->impl = native_method_empty;
	return ret;
}

void native_method_execute(native_method * self, method * parent, vm * vm) {
	self->impl(parent, vm);
}

void native_method_delete(native_method * self) {
	free(self);
}

void native_method_empty(method * parent, vm * vm) {
}
