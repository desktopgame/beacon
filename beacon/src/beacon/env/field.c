#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_factor_interface.h"
#include "generic_type.h"

bc_Field * bc_NewField(bc_StringView namev) {
	bc_Field* ret = (bc_Field*)MEM_MALLOC(sizeof(bc_Field));
	ret->Name = namev;
	ret->Access = ACCESS_PUBLIC_T;
	ret->Modifier = MODIFIER_NONE_T;
	ret->Parent = NULL;
	ret->StaticValue = NULL;
	ret->GType = NULL;
	ret->InitialValue = NULL;
	ret->InitialValueEnv = NULL;
	ret->IsNotInitializedAtCtor = false;
	return ret;
}

void bc_DeleteField(bc_Field * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->InitialValue);
	bc_DeleteEnviroment(self->InitialValueEnv);
	MEM_FREE(self);
}
