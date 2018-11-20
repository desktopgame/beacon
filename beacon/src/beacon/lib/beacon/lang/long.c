#include "long.h"
#include "../../bc_library_interface.h"

bc_Object* bc_NewLong(long value) {
	bc_Long* ret = bc_ConstructObject(sizeof(bc_Long), BC_GENERIC_OBJECT);
	ret->Value = value;
	return (bc_Object*)ret;
}