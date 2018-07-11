#ifndef BEACON_PCODE_CELL_H
#define BEACON_PCODE_CELL_H
#include "../util/vector.h"
#include "../util/tree_map.h"
#include "symbol_interface.h"
#include <stdio.h>

typedef enum cell_tag {
	cell_int_T,
	cell_double_T,
	cell_bool_T,
	cell_char_T,
	cell_string_T,
	cell_symbol_T,
	cell_call_T
} cell_tag;

typedef struct cell {
	cell_tag tag;
	union {
		int int_;
		double double_;
		bool bool_;
		char char_;
		char* str;
		vector* args;
	} u;
} cell;

typedef cell*(*cell_apply)(vector* args, tree_map* ctx);

cell* cell_new(cell_tag tag);

cell* cell_int(int i);

cell* cell_double(double d);

cell* cell_char(char c);

cell* cell_string(const char* str);

cell* cell_bool(bool b);

cell* cell_symbol(char* str);

cell* cell_call(const char* name, ...);

cell* cell_at(cell* self, int index);

cell* cell_eval(cell* code, tree_map* ctx);

int cell_2int(cell* self);

double cell_2double(cell* self);

char cell_2char(cell* self);

char* cell_str(cell* self);

bool cell_atom(cell* self);

void cell_append(cell* self, cell* a);

int cell_fprintf(FILE* fp, cell* c);

void cell_debug(cell* self);

void cell_delete(cell* self);

void cell_symbol_allocate();

int cell_symbol_intern(const char* name, symbol* s);

symbol* cell_symbol_id(int id);

symbol* cell_symbol_key(const char* key);

void cell_define_function_builtin(const char* name, cell_apply a);

void cell_define_function_user(const char* name, vector* parameter_vec,cell* code);

void cell_define_variable(const char* name, cell* value);

void cell_symbol_destroy();
#endif