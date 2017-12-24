#include "field_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "field.h"
#include "../util/text.h"

//proto
static void field_list_delete_impl(list_item item);

field_list * field_list_new() {
	return list_new();
}

void field_list_push(field_list * self, field * child) {
	list_add(self, child);
}

void field_list_dump(field_list * self, int depth) {
	field_list* pointee = self;
	text_putindent(depth);
	printf("field-list");
	text_putline();
	while (1) {
		if (pointee == NULL || pointee->item == NULL) {
			break;
		}
		field* e = (field*)pointee->item;
		field_dump(e, depth + 1);
		pointee = pointee->next;
	}
}

void field_list_delete(field_list * self) {
	list_delete(self, field_list_delete_impl);
}

//private
static void field_list_delete_impl(list_item item) {
	field_delete((field*)item);
}