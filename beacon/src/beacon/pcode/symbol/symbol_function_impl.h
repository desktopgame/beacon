#ifndef BEACON_PCODE_FUNCTION_H
#define BEACON_PCODE_FUNCTION_H
#include "../cell.h"

typedef enum symbol_function_tag {
	symbol_function_user_T,
	symbol_function_blt_T,
} symbol_function_tag;

typedef struct symbol_function {
	symbol_function_tag tag;
	union {
		cell* code;
		cell_apply a_;
	} u;
} symbol_function;

symbol_function* symbol_function_create_c(cell_apply a);

symbol_function* symbol_function_create_lisp(cell* code);

cell* symbol_function_apply(symbol_function* func, cell* args, tree_map* ctx);

void symbol_function_delete(symbol_function* self);
#endif