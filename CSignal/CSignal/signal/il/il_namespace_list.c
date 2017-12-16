#include "il_namespace_list.h"
#include <stdlib.h>
#include <assert.h>

//proto
static void il_namespace_list_delete_impl(list_item item);

il_namespace_list* il_namespace_list_new() {
	return list_new();
}

void il_namespace_list_push(il_namespace_list* self, il_namespace* namespacez) {
	list_add(self, namespacez);
}

void il_namespace_list_dump(il_namespace_list* self, int depth) {
	text_putindent(depth);
	printf("namespace-list");
	text_putline();
	il_namespace_list* pointee = self;
	while(1) {
		if(pointee->item == NULL) {
			break;
		}
		il_namespace* nm = (il_namespace*)pointee->item;
		il_namespace_dump(nm, depth + 1);
		if(pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_namespace_list_delete(il_namespace_list* self) {
	list_delete(self, il_namespace_list_delete_impl);
}

//private
static void il_namespace_list_delete_impl(list_item item) {
	il_namespace* nm = (il_namespace*)item;
	il_namespace_delete(nm);
}