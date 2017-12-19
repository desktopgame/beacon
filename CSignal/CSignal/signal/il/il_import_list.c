#include "il_import_list.h"
#include <stdlib.h>

//proto
static void il_import_list_delete_impl(list_item item);

il_import_list* il_import_list_new() {
	return list_new();
}

void il_import_list_push(il_import_list* self, il_import* child) {
	list_add(self, child);
}

void il_import_list_dump(il_import_list* self, int depth) {
	text_putindent(depth);
	printf("import-list");
	text_putline();
	il_import_list* pointee = self;
	while(1) {
		il_import* imp = (il_import*)pointee->item;
		if (imp == NULL) {
			break;
		}
		il_import_dump(imp, depth + 1);
		if(pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
	text_putline();
}

void il_import_list_delete(il_import_list* self) {
	list_delete(self, il_import_list_delete_impl);
}

//private
static void il_import_list_delete_impl(list_item item) {
	il_import* im = (il_import*)item;
	il_import_delete(im);
}