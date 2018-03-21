#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "type_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "generic_type.h"

field * field_new(const char * name) {
	field* ret = (field*)MEM_MALLOC(sizeof(field));
	ret->name = text_strdup(name);
	ret->gtype = NULL;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->gparent = NULL;
	ret->static_value = NULL;
	return ret;
}

void field_dump(field * self, int depth) {
	assert(self != NULL);
	text_putindent(depth);
	access_print(self->access);
	text_printf(" ");
	modifier_print(self->modifier);
	if (self->gtype == NULL) {
		text_printf(" field NULL %s", self->name);
	} else {
		text_printf(" field ");
		generic_type_print(self->gtype);
		text_printf(" %s", self->name);
	}
	text_putline();
}

void field_delete(field * self) {
	if (self == NULL) {
		return;
	}
	MEM_FREE(self->name);
	MEM_FREE(self);
}
