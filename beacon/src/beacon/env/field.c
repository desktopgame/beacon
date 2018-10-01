#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_factor_interface.h"
#include "generic_type.h"

field * NewField(string_view namev) {
	field* ret = (field*)MEM_MALLOC(sizeof(field));
	ret->namev = namev;
	ret->access = ACCESS_PUBLIC_T;
	ret->modifier = MODIFIER_NONE_T;
	ret->parent = NULL;
	ret->static_value = NULL;
	ret->gtype = NULL;
	ret->initial_value = NULL;
	ret->initial_value_env = NULL;
	ret->not_initialized_at_ctor = false;
	return ret;
}

void DeleteField(field * self) {
	if (self == NULL) {
		return;
	}
	DeleteILFactor(self->initial_value);
	DeleteEnviroment(self->initial_value_env);
	MEM_FREE(self);
}
