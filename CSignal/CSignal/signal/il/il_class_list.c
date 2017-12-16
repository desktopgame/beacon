#include "il_class_list.h"
#include <stdlib.h>

//proto
static void il_class_list_delete_impl(list_item item);

il_class_list* il_class_list_new() {
	return list_new();
}

void il_class_list_push(il_class_list* self, il_class* classz) {
	list_add(self, classz);
}

void il_class_list_dump(il_class_list * self, int depth) {
	text_putindent(depth);
	printf("class-list");
	text_putline();
	il_class_list* pointee = self;
	for (;;) {
		if (pointee->item == NULL) {
			break;
		}
		il_class* cl = (il_class*)pointee->item;
		il_class_dump(cl, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_class_list_delete(il_class_list* self) {
	list_delete(self, il_class_list_delete_impl);
}

//private
static void il_class_list_delete_impl(list_item item) {
	il_class* cl = (il_class*)item;
	il_class_delete(cl);
}