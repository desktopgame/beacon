#include "bc_long.h"
#include "../../bc_library_interface.h"

Object* NewLong(long value) {
	Long* ret = ConstructObject(sizeof(Long), GENERIC_OBJECT);
	ret->Value = value;
	return (Object*)ret;
}