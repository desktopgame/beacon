#include "il_class.h"
#include <stdlib.h>
#include "../util/text.h"
#include "il_method_list.h"
#include "il_field.h"

//proto
static void il_class_field_delete(vector_item item);

il_class* il_class_new(const char* name) {
	il_class* ret = (il_class*)malloc(sizeof(il_class));
	ret->name = text_strdup(name);
	ret->super = NULL;
	ret->field_list = vector_new();
	ret->method_list = il_method_list_new();
	return ret;
}

void il_class_dump(il_class * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		il_field* ilf = (il_field*)e;
		il_field_dump(ilf, depth + 1);
	}
	il_method_list_dump(self->method_list, depth + 1);
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	free(self->name);
	il_type_delete(self->super);
	vector_delete(self->field_list, il_class_field_delete);
	il_method_list_delete(self->method_list);
	free(self);
}

//private
static void il_class_field_delete(vector_item item) {
	il_field* e = (il_field*)item;
	il_field_delete(e);
}