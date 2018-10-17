#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void il_enum_name_delete(il_enum* self);

il_type * WrapILEnum(il_enum * self) {
	il_type* ret = NewILType();
	ret->tag = ilTYPE_ENUM_T;
	ret->u.enum_ = self;
	return ret;
}

il_enum * NewILEnum(StringView namev) {
	il_enum* ret = (il_enum*)MEM_MALLOC(sizeof(il_enum));
	ret->namev = namev;
	ret->item_vec = NewVector();
	return ret;
}

void DeleteILEnum(il_enum * self) {
	DeleteVector(self->item_vec, il_enum_name_delete);
	MEM_FREE(self);
}

//private
static void il_enum_name_delete(il_enum* self) {

}
