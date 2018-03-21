#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void il_enum_name_delete(il_enum* self);

il_type * il_type_wrap_enum(il_enum * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_enum;
	ret->u.enum_ = self;
	return ret;
}

il_enum * il_enum_new(const char * name) {
	il_enum* ret = (il_enum*)MEM_MALLOC(sizeof(il_enum));
	ret->name = text_strdup(name);
	ret->item_vec = vector_new();
	return ret;
}

void il_enum_dump(il_enum * self, int depth) {
	text_putindent(depth);
	text_printf("enum %s", self->name);
	text_putline();
	for (int i = 0; i < self->item_vec->length; i++) {
		char* str = (char*)vector_at(self->item_vec, i);

		text_putindent(depth + 1);
		text_printf("%s", str);
		text_putline();
	}
}

void il_enum_delete(il_enum * self) {
	MEM_FREE(self->name);
	vector_delete(self->item_vec, il_enum_name_delete);
	MEM_FREE(self);
}

//private
static void il_enum_name_delete(il_enum* self) {

}
