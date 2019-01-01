#include "field.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../il/il_factor_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "generic_type.h"
#include "type_interface.h"

bc_Field* bc_NewField(bc_StringView namev) {
        bc_Field* ret = (bc_Field*)MEM_MALLOC(sizeof(bc_Field));
        ret->Name = namev;
        ret->StaticValue = NULL;
        ret->GType = NULL;
        ret->InitialValue = NULL;
        ret->InitialValueEnv = NULL;
        ret->IsNotInitializedAtCtor = false;
        bc_InitMember((bc_Member*)ret);
        return ret;
}

void bc_DeleteField(bc_Field* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteILFactor(self->InitialValue);
        bc_DeleteEnviroment(self->InitialValueEnv);
        MEM_FREE(self);
}
