#ifndef BEACON_PCODE_CELL_H
#define BEACON_PCODE_CELL_H
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include "../util/vector.h"
#include "../util/tree_map.h"
struct symbol;

/**
 * セルの種類を表すタグ.
 */
typedef enum cell_tag {
	cell_nil_T,
	cell_int_T,
	cell_double_T,
	cell_char_T,
	cell_bool_T,
	cell_string_T,
	cell_cons_T,
	cell_symbol_T,
	cell_scope_T
} cell_tag;

//
//(scope ((name 0) (age 10))
//)
//

typedef struct cell {
	cell_tag tag;
	union {
		int int_;
		double double_;
		bool bool_;
		char char_;
		char* string_;
		struct cell* first;
	} u;
	struct cell* rest;
} cell;

/**
 * 関数の評価器です.
 */
typedef cell*(*cell_apply)(cell* args, tree_map* ctx);

#define cell_new(tag) (cell_malloc(tag, __FILE__, __LINE__))
#define cell_lists(...) (cell_list(-1, __VA_ARGS__))
#define eval_at(args, index, ctx) (cell_scoped_eval(cell_at(args, index), ctx))

cell* cell_malloc(cell_tag tag, const char* filename, int lineno);

cell* cell_int(int i);

cell* cell_double(double d);

cell* cell_string(const char* str);

cell* cell_function(const char* str);

cell* cell_identifier(const char* str);

cell* cell_bool(bool a);

cell* cell_true();

cell* cell_false();

cell* cell_nil();

cell* cell_cons(cell* a, cell* b);

cell* cell_list(int len, ...);

cell* cell_call(const char* name, ...);

cell* cell_append(cell* self, cell* a);

cell* cell_dup(cell* src);

cell* cell_eval(cell* code);

cell* cell_scoped_eval(cell* code, tree_map* ctx);

cell* cell_at(cell* code, int index);

bool cell_numberp(cell* self);

bool cell_consp(cell* self);

bool cell_atomp(cell* self);

bool cell_eq(cell* a, cell* b);

bool cell_blank(cell* a);

bool cell_2bool(cell* a);

const char* cell_2str(cell* a);

tree_map* cell_2map(cell* params, cell* args, tree_map* ctx);

void cell_delete(cell* self);

int cell_fprintf(FILE* fp, cell* a);

void cell_debug(cell* temp);

void cell_symbol_allocate();

void cell_symbol_destroy();

int cell_symbol_intern(const char* name, struct symbol* s);

struct symbol* cell_symbol_id(int id);

struct symbol* cell_symbol_key(const char* name);
#endif