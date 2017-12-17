#include "il_method_list.h"
#include "../util/text.h"
#include <stdlib.h>

//proto
static void il_method_list_delete_impl(list_item item);

il_method_list * il_method_list_new() {
	return list_new();
}

void il_method_list_push(il_method_list * self, il_method * child) {
	list_add(self, child);
}

void il_method_list_dump(il_method_list * self, int depth) {
	text_putindent(depth);
	printf("method-list");
	text_putline();
	il_method_list* pointee = self;
	while (1) {
		if (pointee->item == NULL) {
			break;
		}
		il_method_list* fi = (il_method_list*)pointee->item;
		il_method_dump(fi, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_method_list_delete(il_method_list * self) {
	list_delete(self, il_method_list_delete_impl);
}

//private
static void il_method_list_delete_impl(list_item item) {
	il_method* mt = (il_method*)item;
	il_method_delete(mt);
}