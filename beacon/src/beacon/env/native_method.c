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

NativeMethod * NewNativeMethod() {
	NativeMethod* ret = (NativeMethod*)MEM_MALLOC(sizeof(NativeMethod));
	ret->ref = NULL;
	return ret;
}

void ExecuteNativeMethod(NativeMethod * self, Method * parent, Frame* fr, Enviroment* env) {
	if (self->ref == NULL) {
		class_* declared = parent->Parent->u.class_;
		self->ref = GetNumericMapValue(declared->NativeMethodRef_nmap, parent->Name);
	}
	self->ref->Body(parent, fr, env);
}

void DeleteNativeMethod(NativeMethod * self) {
	MEM_FREE(self);
}