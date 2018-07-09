#include "symbol_interface.h"
#include "symbol_impl.h"
#include "../util/mem.h"
#include <assert.h>

static symbol* symbol_malloc(const char* filename, int lineno);
#define symbol_new() (symbol_malloc(__FILE__, __LINE__))

symbol* symbol_function_c(cell_apply a) {
	symbol* ret = symbol_new();
	ret->tag = symbol_function_T;
	ret->u.func_ = symbol_function_create_c(a);
	return ret;
}

symbol* symbol_function_lisp(cell* code) {
	symbol* ret = symbol_new();
	ret->tag = symbol_function_T;
	ret->u.func_ = symbol_function_create_lisp(code);
	return ret;
}

symbol* symbol_variable(cell* var) {
	symbol* ret = symbol_new();
	ret->tag = symbol_variable;
	ret->u.var = var;
	return ret;
}

cell* symbol_function_call(symbol* self, cell* args) {
	assert(self->tag == symbol_function_T);
	symbol_function* f = self->u.func_;
	return symbol_function_apply(f, args);
}

void symbol_delete(symbol* self) {
	MEM_FREE(self);
}

//private
static symbol* symbol_malloc(const char* filename, int lineno) {
	symbol* ret = (symbol*)mem_malloc(sizeof(symbol), filename, lineno);
	return ret;
}