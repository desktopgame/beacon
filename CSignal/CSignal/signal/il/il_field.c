#include "il_field.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"

il_field * il_field_new(const char * name) {
	il_field* ret = (il_field*)malloc(sizeof(il_field));
	ret->type = NULL;
	ret->access = access_public;
	ret->modifier = modifier_none;
	ret->name = text_strdup(name);
	return ret;
}

void il_field_dump(il_field * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	printf(" field %s %s", self->type->name, self->name);
	text_putline();
}

void il_field_delete(il_field * self) {
	if (self == NULL) {
		return;
	}
	il_type_delete(self->type);
	free(self->name);
	free(self);
}
