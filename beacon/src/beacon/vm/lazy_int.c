#include "lazy_int.h"
#include "../util/mem.h"

lazy_int* lazy_int_new(int value) {
	lazy_int* ret = (lazy_int*)MEM_MALLOC(sizeof(lazy_int));
	ret->value = value;
	return ret;
}

void lazy_int_delete(lazy_int* self) {
	MEM_FREE(self);
}