#include "il_property_body.h"
#include "../util/mem.h"
#include "../env/generic_cache.h"
#include "../util/text.h"
#include "il_stmt_interface.h"

static void il_property_body_stmt_delete(vector_item item);

il_property_body* il_property_body_malloc(il_property_body_tag tag, const char* filename, int lineno) {
	il_property_body* ret = mem_malloc(sizeof(il_property_body), filename, lineno);
	ret->statement_list = vector_new();
	ret->tag = tag;
	ret->is_short = false;
	return ret;
}

void il_property_body_dump(il_property_body* self, int depth) {
	io_printi(depth);
	access_print(self->access);
	printf(" ");
	if(self->tag == ilproperty_set_T) {
		printf("set");
	} else {
		printf("get");
	}
	if(self->is_short) {
		printf(" simple");
	}
	io_println();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_property_body_delete(il_property_body* self) {
	vector_delete(self->statement_list, il_property_body_stmt_delete);
	MEM_FREE(self);
}
//private
static void il_property_body_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}