#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void ILEnum_name_delete(ILEnum* self);

bc_ILType * WrapILEnum(ILEnum * self) {
	bc_ILType* ret = bc_NewILType();
	ret->Tag = ILTYPE_ENUM_T;
	ret->Kind.Enum = self;
	return ret;
}

ILEnum * NewILEnum(bc_StringView namev) {
	ILEnum* ret = (ILEnum*)MEM_MALLOC(sizeof(ILEnum));
	ret->Name = namev;
	ret->Items = bc_NewVector();
	return ret;
}

void DeleteILEnum(ILEnum * self) {
	bc_DeleteVector(self->Items, ILEnum_name_delete);
	MEM_FREE(self);
}

//private
static void ILEnum_name_delete(ILEnum* self) {

}
