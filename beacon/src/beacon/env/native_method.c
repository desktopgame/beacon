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

bc_NativeMethod * bc_NewNativeMethod() {
	bc_NativeMethod* ret = (bc_NativeMethod*)MEM_MALLOC(sizeof(bc_NativeMethod));
	ret->Ref = NULL;
	return ret;
}

void bc_ExecuteNativeMethod(bc_NativeMethod * self, bc_Method * parent, Frame* fr, Enviroment* env) {
	if (self->Ref == NULL) {
		bc_Class* declared = parent->Parent->Kind.Class;
		self->Ref = GetNumericMapValue(declared->NativeMethodRefMap, parent->Name);
	}
	self->Ref->Body(parent, fr, env);
}

void bc_DeleteNativeMethod(bc_NativeMethod * self) {
	MEM_FREE(self);
}