#include "il_class.h"
#include <stdlib.h>
#include "../util/text.h"
#include "il_field_list.h"

il_class* il_class_new(const char* name) {
	il_class* ret = (il_class*)malloc(sizeof(il_class));
	ret->name = text_strdup(name);
	ret->super = NULL;
	ret->field_list = il_field_list_new();
	return ret;
}

void il_class_dump(il_class * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	il_field_list_dump(self->field_list, depth + 1);
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	free(self->name);
	il_type_delete(self->super);
	il_field_list_delete(self->field_list);
	free(self);
}
