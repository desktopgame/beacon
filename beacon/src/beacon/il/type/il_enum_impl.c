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
	ret->item_vec = NewVector();
	return ret;
}

void il_enum_delete(il_enum * self) {
	DeleteVector(self->item_vec, il_enum_name_delete);
	MEM_FREE(self);
}

//private
static void il_enum_name_delete(il_enum* self) {

}
