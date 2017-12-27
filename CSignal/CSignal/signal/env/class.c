#include "class.h"
#include "../util/text.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "field.h"
#include "method.h"

//private
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);

class_ * class_new(const char * name, class_type type) {
	assert(name != NULL);
	class_* ret = (class_*)malloc(sizeof(class_));
	ret->name = text_strdup(name);
	ret->type = type;
	ret->location = NULL;
	ret->state = class_none;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->field_list = vector_new();
	ret->method_list = vector_new();
	return ret;
}

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	printf("class %s", self->name);
	text_putline();
	//フィールドの一覧をダンプ
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
}

void class_delete(class_ * self) {
	assert(self->ref_count == 0);
	free(self->name);
	if (self->super_class != NULL) {
		self->super_class->ref_count--;
	}
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	free(self);
}

//private
static void class_field_delete(vector_item item) {
	field* e = (field*)item;
	field_delete(e);
}

static void class_method_delete(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}