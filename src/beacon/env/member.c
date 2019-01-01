#include "member.h"
#include <stdlib.h>

void bc_InitMember(bc_Member* self) {
        self->Parent = NULL;
        self->Modifier = MODIFIER_NONE_T;
        self->Access = ACCESS_PUBLIC_T;
}