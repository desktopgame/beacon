#include "native_method.h"
#include <stdlib.h>
#include "../util/mem.h"
#include "../vm/vm.h"
#include "TYPE_IMPL.h"
#include "generic_type.h"
#include "method.h"
#include "native_method_ref.h"
#include "object.h"
#include "type_interface.h"

bc_NativeMethod* bc_NewNativeMethod() {
        bc_NativeMethod* ret =
            (bc_NativeMethod*)MEM_MALLOC(sizeof(bc_NativeMethod));
        ret->Ref = NULL;
        return ret;
}

void bc_ExecuteNativeMethod(bc_NativeMethod* self, bc_Method* parent,
                            bc_Frame* fr, bc_Enviroment* env) {
        if (self->Ref == NULL) {
                bc_Class* declared = BC_MEMBER_TYPE(parent)->Kind.Class;
                self->Ref = bc_GetNumericMapValue(declared->NativeMethodRefMap,
                                                  parent->Name);
        }
        self->Ref->Body(parent, fr, env);
}

void bc_DeleteNativeMethod(bc_NativeMethod* self) { MEM_FREE(self); }