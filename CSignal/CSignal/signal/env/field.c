#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "class.h"
#include "../util/mem.h"
#include "../util/text.h"

field * field_new(const char * name) {
	field* ret = (field*)MEM_MALLOC(sizeof(field));
	ret->name = text_strdup(name);
	ret->type = NULL;
	ret->access = access_public;
	ret->modifier = modifier_none;
	return ret;
}

void field_dump(field * self, int depth) {
	assert(self != NULL);
	text_putindent(depth);
	access_print(self->access);
	printf(" ");
	modifier_print(self->modifier);
	if (self->type == NULL) {
		printf(" field NULL %s", self->name);
	} else {
		printf(" field %s %s", self->type->name,self->name);
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
