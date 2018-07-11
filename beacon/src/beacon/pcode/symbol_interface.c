#include "symbol_interface.h"
#include "symbol/symbol_function_impl.h"
#include "../util/mem.h"

symbol* symbol_new(symbol_tag tag) {
	symbol* ret = (symbol*)MEM_MALLOC(sizeof(symbol));
	ret->tag = tag;
	return ret;
}

void symbol_delete(symbol* self) {
	if(self->tag == symbol_function_T) {
		symbol_function_delete(self->u.func);
	}
	MEM_FREE(self);
}