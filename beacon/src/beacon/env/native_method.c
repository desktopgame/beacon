#include "native_method.h"
#include <stdlib.h>
#include "method.h"
#include "type_interface.h"
#include "type_impl.h"
#include "object.h"
#include "../vm/vm.h"
#include "../util/mem.h"
#include "native_method_ref.h"
#include "generic_type.h"

native_method * native_method_new() {
	native_method* ret = (native_method*)MEM_MALLOC(sizeof(native_method));
	ret->ref = NULL;
	return ret;
}

void native_method_execute(native_method * self, method * parent, vm * vm, enviroment* env) {
	if (self->ref == NULL) {
		class_* declared = parent->parent->u.class_;
		self->ref = tree_map_get(declared->native_method_ref_map, parent->name);
	}
	self->ref->impl(parent, vm, env);
}

void native_method_delete(native_method * self) {
//	native_method_ref_delete(self->ref);
	MEM_FREE(self);
}

void native_method_empty(method * parent, vm * vm) {
}
