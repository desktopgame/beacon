#ifndef BEACON_PCODE_SYMBOL_INTERFACE_H
#define BEACON_PCODE_SYMBOL_INTERFACE_H
//#include "cell.h"
typedef enum symbol_tag {
	symbol_variable_T,
	symbol_function_T,
} symbol_tag;

struct cell;
struct symbol_function;
typedef struct symbol {
	symbol_tag tag;
	union {
		struct symbol_function* func;
		struct cell* code;
	} u;
} symbol;

symbol* symbol_new(symbol_tag tag);

void symbol_delete(symbol* self);
#endif