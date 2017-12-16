#include "il_field_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"

//proto
static void il_field_list_delete_impl(list_item item);

il_field_list * il_field_list_new() {
	return list_new();
}

void il_field_list_push(il_field_list * self, il_field * field) {
	list_add(self, field);
}

void il_field_list_dump(il_field_list * self, int depth) {
	text_putindent(depth);
	printf("field-list");
	text_putline();
	il_field_list* pointee = self;
	while (1) {
		if (pointee->item == NULL) {
			break;
		}
		il_field* fi = (il_field*)pointee->item;
		il_field_dump(fi, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_field_list_delete(il_field_list * self) {
	list_delete(self, il_field_list_delete_impl);
}

//private
static void il_field_list_delete_impl(list_item item) {
	il_field* fi = (il_field*)item;
	il_field_delete(fi);
}
