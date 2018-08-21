#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../il/il_factor_interface.h"
#include "generic_type.h"

field * field_new(string_view namev) {
	field* ret = (field*)MEM_MALLOC(sizeof(field));
	ret->namev = namev;
	ret->access = access_public_T;
	ret->modifier = modifier_none_T;
	ret->parent = NULL;
	ret->static_value = NULL;
	ret->gtype = NULL;
	ret->initial_value = NULL;
	ret->initial_value_env = NULL;
	ret->not_initialized_at_ctor = false;
	return ret;
}

void field_delete(field * self) {
	if (self == NULL) {
		return;
	}
	il_factor_delete(self->initial_value);
	enviroment_delete(self->initial_value_env);
	MEM_FREE(self);
}
