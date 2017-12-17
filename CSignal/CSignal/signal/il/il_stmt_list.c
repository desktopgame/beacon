#include "il_stmt_list.h"
#include <stdlib.h>
#include <assert.h>

//proto
static void il_stmt_list_delete_impl(list_item item);

il_stmt_list * il_stmt_list_new() {
	return list_new();
}

void il_stmt_list_push(il_stmt_list * self, il_stmt * child) {
	list_add(self, child);
}

void il_stmt_list_dump(il_stmt_list * self, int depth) {
	assert(self != NULL);
	text_putindent(depth);
	printf("stmt-list");
	text_putline();
	il_stmt_list* pointee = self;
	if (pointee == NULL) {
		return;
	}
	while (1) {
		if (pointee->item == NULL) {
			break;
		}
		il_stmt* param = (il_stmt*)pointee->item;
		il_stmt_dump(param, depth + 1);
		//il_parameter_dump(param, depth + 1);
		if (pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_stmt_list_delete(il_stmt_list * self) {
	list_delete(self, il_stmt_list_delete_impl);
}

//private
static void il_stmt_list_delete_impl(list_item item) {
	il_stmt* st = (il_stmt*)item;
	il_stmt_delete(st);
}
