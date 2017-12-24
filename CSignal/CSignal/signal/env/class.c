#include "class.h"
#include "../util/text.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "field_list.h"
#include "method_list.h"
#include "../util/text.h"

class_ * class_new(const char * name, class_type type) {
	assert(name != NULL);
	class_* ret = (class_*)malloc(sizeof(class_));
	ret->name = text_strdup(name);
	ret->type = type;
	ret->location = NULL;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->field_list = field_list_new();
	ret->method_list = method_list_new();
	return ret;
}

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	field_list_dump(self->field_list, depth + 1);
	method_list_dump(self->method_list, depth + 1);
}

void class_delete(class_ * self) {
	assert(self->ref_count == 0);
	free(self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	field_list_delete(self->field_list);
	method_list_delete(self->method_list);
	free(self);
}
