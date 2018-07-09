#ifndef BEACON_PCODE_SYMBOL_H
#define BEACON_PCODE_SYMBOL_H
#include "cell.h"

typedef enum symbol_tag {
	symbol_function_T,
	symbol_variable_T
} symbol_tag;

struct symbol_function;
typedef struct symbol {
	symbol_tag tag;
	union {
		struct symbol_function* func_;
		cell* var;
	} u;
} symbol;

symbol* symbol_function_c(cell_apply a);

symbol* symbol_function_lisp(cell* code);

symbol* symbol_variable(cell* var);

cell* symbol_function_call(symbol* self, cell* args);

void symbol_delete(symbol* self);
#endif