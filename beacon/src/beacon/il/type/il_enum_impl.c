#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void ILEnum_name_delete(bc_ILEnum* self);

bc_ILType * bc_WrapILEnum(bc_ILEnum * self) {
	bc_ILType* ret = bc_NewILType();
	ret->Tag = ILTYPE_ENUM_T;
	ret->Kind.Enum = self;
	return ret;
}

bc_ILEnum * bc_NewILEnum(bc_StringView namev) {
	bc_ILEnum* ret = (bc_ILEnum*)MEM_MALLOC(sizeof(bc_ILEnum));
	ret->Name = namev;
	ret->Items = bc_NewVector();
	return ret;
}

void bc_DeleteILEnum(bc_ILEnum * self) {
	bc_DeleteVector(self->Items, ILEnum_name_delete);
	MEM_FREE(self);
}

//private
static void ILEnum_name_delete(bc_ILEnum* self) {

}
