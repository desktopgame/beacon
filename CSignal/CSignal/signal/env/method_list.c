#include "method_list.h"
#include <stdlib.h>
#include <stdio.h>
#include "method.h"
#include "../util/text.h"
#include "../util/list.h"

//proto
static void method_list_delete_impl(list_item item);

method_list * method_list_new() {
	return list_new();
}

void method_list_push(method_list * self, method * child) {
	list_add(self, child);
}

void method_list_dump(method_list * self, int depth) {
	method_list* pointee = self;
	text_putindent(depth);
	printf("method-list");
	text_putline();
	while (1) {
		if (pointee == NULL || pointee->item == NULL) {
			break;
		}
		method* e = (method*)pointee->item;
		method_dump(e, depth + 1);
		pointee = pointee->next;
	}
}

void method_list_delete(method_list * self) {
	list_delete(self, method_list_delete_impl);
}

//private
static void method_list_delete_impl(list_item item) {
	method_delete((method*)item);
}