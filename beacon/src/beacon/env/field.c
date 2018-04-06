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
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->parent = NULL;
	ret->static_value = NULL;
	return ret;
}

void field_dump(field * self, int depth) {
	assert(self != NULL);
	text_putindent(depth);
	access_print(self->access);
	text_printf(" ");
	modifier_print(self->modifier);
	text_printf(" field ");
	virtual_type_print(&self->vtype);
	text_printf(" %s", self->name);
	text_putline();
}

void field_delete(field * self) {
	if (self == NULL) {
		return;
	}
	if(self->vtype.tag == virtualtype_default) {
		generic_type_delete(self->vtype.u.gtype);
	}
	MEM_FREE(self->name);
	MEM_FREE(self);
}
