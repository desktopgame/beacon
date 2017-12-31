#include "il_class.h"
#include <stdlib.h>
#include "../util/text.h"
#include "il_field.h"
#include "il_method.h"
#include "il_constructor.h"
#include "../util/mem.h"

//proto
static void il_class_field_delete(vector_item item);
static void il_class_method_delete(vector_item item);

il_class* il_class_new(const char* name) {
	il_class* ret = (il_class*)MEM_MALLOC(sizeof(il_class));
	ret->name = text_strdup(name);
	ret->super = NULL;
	ret->field_list = vector_new();
	ret->method_list = vector_new();
	ret->constructor_list = vector_new();
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
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		il_method* ilm = (il_method*)e;
		il_method_dump(ilm, depth + 1);
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		il_constructor* ilcons = (il_constructor*)e;
		il_constructor_dump(ilcons, depth + 1);
	}
}

void il_class_delete(il_class * self) {
	if (self == NULL) {
		return;
	}
	//printf("free class %s\n", self->name);
	MEM_FREE(self->name);
	il_type_delete(self->super);
	vector_delete(self->field_list, il_class_field_delete);
	vector_delete(self->method_list, il_class_method_delete);
	MEM_FREE(self);
}

//private
static void il_class_field_delete(vector_item item) {
	il_field* e = (il_field*)item;
	il_field_delete(e);
}

static void il_class_method_delete(vector_item item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}