#include "bc_long.h"
#include "../../bc_library_interface.h"

bc_Object* NewLong(long value) {
	Long* ret = bc_ConstructObject(sizeof(Long), BC_GENERIC_OBJECT);
	ret->Value = value;
	return (bc_Object*)ret;
}