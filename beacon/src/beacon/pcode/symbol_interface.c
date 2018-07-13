#include "symbol_interface.h"
#include "symbol/symbol_function_impl.h"
#include "../util/mem.h"

symbol* symbol_new(symbol_tag tag) {
	symbol* ret = (symbol*)MEM_MALLOC(sizeof(symbol));
	ret->tag = tag;
	return ret;
}

void symbol_mark_recursive(symbol* self) {
	if(self->tag == symbol_variable_T) {
		cell_mark_recursive(self->u.code);
	} else if(self->tag == symbol_function_T) {
		symbol_function* f = self->u.func;
		if(f->tag == symbol_function_user) {
			cell_mark_recursive(f->u.userF->params);
			cell_mark_recursive(f->u.userF->code);
		}
	}
}

void symbol_delete(symbol* self) {
	if(self->tag == symbol_function_T) {
		symbol_function_delete(self->u.func);
	}
	MEM_FREE(self);
}