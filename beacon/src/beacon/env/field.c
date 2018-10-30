#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_factor_interface.h"
#include "generic_type.h"

Field * NewField(StringView namev) {
	Field* ret = (Field*)MEM_MALLOC(sizeof(Field));
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

void DeleteField(Field * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->InitialValue);
	DeleteEnviroment(self->InitialValueEnv);
	MEM_FREE(self);
}
