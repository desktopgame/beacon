#include "field.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../util/text.h"

field * field_new(const char * name) {
	field* ret = (field*)malloc(sizeof(field));
	ret->name = text_strdup(name);
	ret->type = NULL;
	return ret;
}

void field_dump(field * self, int depth) {
	assert(self != NULL);
	text_putindent(depth);
	printf("field %s", self->name);
	text_putline();
}

void field_delete(field * self) {
	if (self == NULL) {
		return;
	}
	free(self->name);
	free(self);
}
