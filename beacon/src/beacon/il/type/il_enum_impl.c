#include "il_enum_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

//proto
static void ILEnum_name_delete(ILEnum* self);

ILType * WrapILEnum(ILEnum * self) {
	ILType* ret = NewILType();
	ret->Tag = ILTYPE_ENUM_T;
	ret->Kind.Enum = self;
	return ret;
}

ILEnum * NewILEnum(StringView namev) {
	ILEnum* ret = (ILEnum*)MEM_MALLOC(sizeof(ILEnum));
	ret->Name = namev;
	ret->Items = NewVector();
	return ret;
}

void DeleteILEnum(ILEnum * self) {
	DeleteVector(self->Items, ILEnum_name_delete);
	MEM_FREE(self);
}

//private
static void ILEnum_name_delete(ILEnum* self) {

}
