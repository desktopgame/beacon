#include "il_parameter_list.h"
#include "../util/text.h"
#include <stdio.h>

//proto
static void il_parameter_list_delete_impl(list_item item);

il_parameter_list * il_parameter_list_new() {
	return list_new();
}

void il_parameter_list_push(il_parameter_list * self, il_parameter * param) {
	list_add(self, param);
}

void il_parameter_list_dump(il_parameter_list * self, int depth) {
	text_putindent(depth);
	printf("parameter-list");
	text_putline();
	il_parameter_list* pointee = self;
	while (1) {
		if (pointee->item == NULL) {
			break;
		}
		il_parameter_list* param = (il_parameter_list*)pointee->item;
		il_parameter_dump(param, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_parameter_list_delete(il_parameter_list * self) {
	list_delete(self, il_parameter_list_delete_impl);
}

//private
static void il_parameter_list_delete_impl(list_item item) {
	il_parameter* param = (il_parameter*)item;
	il_parameter_delete(param);
}
