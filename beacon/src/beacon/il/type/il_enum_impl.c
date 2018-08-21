#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void il_enum_name_delete(il_enum* self);

il_type * il_type_wrap_enum(il_enum * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_enum_T;
	ret->u.enum_ = self;
	return ret;
}

il_enum * il_enum_new(string_view namev) {
	il_enum* ret = (il_enum*)MEM_MALLOC(sizeof(il_enum));
	ret->namev = namev;
	ret->item_vec = vector_new();
	return ret;
}

void il_enum_dump(il_enum * self, int depth) {
	io_printi(depth);
	printf("enum %s", string_pool_ref2str(self->namev));
	io_println();
	for (int i = 0; i < self->item_vec->length; i++) {
		const char* str = string_pool_ref2str((string_view)vector_at(self->item_vec, i));

		io_printi(depth + 1);
		printf("%s", str);
		io_println();
	}
}

void il_enum_delete(il_enum * self) {
	vector_delete(self->item_vec, il_enum_name_delete);
	MEM_FREE(self);
}

//private
static void il_enum_name_delete(il_enum* self) {

}
