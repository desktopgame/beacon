#include "native_method.h"
#include <stdlib.h>
#include "method.h"
#include "../vm/vm.h"
#include "native_method_ref.h"

native_method * native_method_new() {
	native_method* ret = (native_method*)malloc(sizeof(native_method));
	ret->ref = NULL;
	return ret;
}

void native_method_execute(native_method * self, method * parent, vm * vm) {
	self->ref->impl(parent, vm);
}

void native_method_delete(native_method * self) {
	native_method_ref_delete(self->ref);
	free(self);
}

void native_method_empty(method * parent, vm * vm) {
}
