#include "native_method.h"
#include <stdlib.h>
#include "method.h"
#include "type_interface.h"
#include "TYPE_IMPL.h"
#include "object.h"
#include "../vm/vm.h"
#include "../util/mem.h"
#include "native_method_ref.h"
#include "generic_type.h"

native_method * NewNativeMethod() {
	native_method* ret = (native_method*)MEM_MALLOC(sizeof(native_method));
	ret->ref = NULL;
	return ret;
}

void ExecuteNativeMethod(native_method * self, method * parent, frame * fr, Enviroment* env) {
	if (self->ref == NULL) {
		class_* declared = parent->parent->u.class_;
		self->ref = GetNumericMapValue(declared->native_method_ref_nmap, parent->namev);
	}
	self->ref->impl(parent, fr, env);
}

void DeleteNativeMethod(native_method * self) {
	MEM_FREE(self);
}