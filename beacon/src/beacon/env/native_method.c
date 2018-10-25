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

void ExecuteNativeMethod(native_method * self, Method * parent, Frame* fr, Enviroment* env) {
	if (self->ref == NULL) {
		class_* declared = parent->Parent->u.class_;
		self->ref = GetNumericMapValue(declared->NativeMethodRef_nmap, parent->Name);
	}
	self->ref->Body(parent, fr, env);
}

void DeleteNativeMethod(native_method * self) {
	MEM_FREE(self);
}