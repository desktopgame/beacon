#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "generic_type.h"

field * field_new(string_view namev) {
	field* ret = (field*)MEM_MALLOC(sizeof(field));
	ret->namev = namev;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->parent = NULL;
	ret->static_value = NULL;
	ret->gtype = NULL;
	return ret;
}

void field_delete(field * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self);
}
