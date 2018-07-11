#ifndef BEACON_PCODE_SYMBOL_SYMBOL_FUNCTION_IMPL_H
#define BEACON_PCODE_SYMBOL_SYMBOL_FUNCTION_IMPL_H
#include "../cell.h"

typedef enum symbol_function_tag {
	symbol_function_builtin,
	symbol_function_user
} symbol_function_tag;

typedef struct user_function {
	vector* parameter_vec;
	cell* code;
} user_function;

typedef struct symbol_function {
	symbol_function_tag tag;
	union {
		user_function* userF;
		cell_apply a;
	} u;
} symbol_function;

symbol_function* symbol_function_new(symbol_function_tag tag);

symbol_function* symbol_function_new_builtin(cell_apply a);

symbol_function* symbol_function_new_user(vector* parameter_vec, cell* code);

cell* symbol_function_apply(symbol_function* self, cell* cArgs, tree_map* ctx);

void symbol_function_delete(symbol_function* self);
#endif