#include "il_argument_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"

//proto
static void il_argument_list_delete_impl(list_item item);

il_argument_list * il_argument_list_new() {
	return list_new();
}

void il_argument_list_push(il_argument_list * self, il_argument * child) {
	list_add(self, child);
}

void il_argument_list_dump(il_argument_list * self, int depth) {
	text_putindent(depth);
	printf("argument-list");
	text_putline();
	il_argument_list* pointee = self;
	for (;;) {
		if (pointee->item == NULL) {
			break;
		}
		il_argument* cl = (il_argument*)pointee->item;
		il_argument_dump(cl, depth + 1);
		//il_class_dump(cl, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_argument_list_delete(il_argument_list * self) {
	list_delete(self, il_argument_list_delete_impl);
}

//private
static void il_argument_list_delete_impl(list_item item) {
	il_argument* ar = (il_argument*)item;
	il_argument_delete(ar);
}