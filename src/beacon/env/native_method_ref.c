#include "native_method_ref.h"
#include <stdlib.h>
#include "../util/mem.h"

bc_NativeMethodRef* bc_NewNativeMethodRef(bc_NativeImpl impl) {
        bc_NativeMethodRef* ret =
            (bc_NativeMethodRef*)MEM_MALLOC(sizeof(bc_NativeMethodRef));
        ret->Body = impl;
        return ret;
}

void bc_DeleteNativeMethodRef(bc_NativeMethodRef* self) { MEM_FREE(self); }
