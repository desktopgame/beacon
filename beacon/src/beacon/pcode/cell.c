#include "cell.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "symbol_interface.h"
#include "symbol/symbol_function_impl.h"
#include <assert.h>

#define args_check(v, size) assert((v->length - 1) == size)
#define args_at(v, index) (vector_at(v, index + 1))
#define args_first(v) (vector_at(v, 1))
#define args_second(v) (vector_at(v, 2))

static void cell_cell_delete(vector_item item);
static void cell_symbol_delete(vector_item item);
static tree_map* gMap = NULL;
static vector* gVec = NULL;
static vector* gHeap = NULL;

static cell* blt_print(vector* args, tree_map* ctx);
static cell* blt_println(vector* args, tree_map* ctx);

static cell* blt_add(vector* args, tree_map* ctx);
static cell* blt_sub(vector* args, tree_map* ctx);
static cell* blt_mul(vector* args, tree_map* ctx);
static cell* blt_div(vector* args, tree_map* ctx);
static cell* blt_mod(vector* args, tree_map* ctx);

static cell* blt_gt(vector* args, tree_map* ctx);
static cell* blt_ge(vector* args, tree_map* ctx);
static cell* blt_lt(vector* args, tree_map* ctx);
static cell* blt_le(vector* args, tree_map* ctx);
static cell* blt_eval(vector* args, tree_map* ctx);
static cell* blt_progn(vector* args, tree_map* ctx);
static cell* blt_defun(vector* args, tree_map* ctx);
static cell* blt_defvar(vector* args, tree_map* ctx);
static cell* blt_let(vector* args, tree_map* ctx);

cell* cell_new(cell_tag tag) {
	cell* ret = (cell*)MEM_MALLOC(sizeof(cell));
	ret->tag = tag;
	if(tag == cell_call_T) {
		ret->u.vec = vector_new();
	}
	//vector_push(gHeap, ret);
	return ret;
}

cell* cell_int(int i) {
	cell* ret = cell_new(cell_int_T);
	ret->u.int_ = i;
	return ret;
}

cell* cell_double(double d) {
	cell* ret = cell_new(cell_double_T);
	ret->u.double_ = d;
	return ret;
}

cell* cell_char(char c) {
	cell* ret = cell_new(cell_char_T);
	ret->u.char_ = c;
	return ret;
}

cell* cell_string(const char* str) {
	cell* ret = cell_new(cell_string_T);
	ret->u.str = text_strdup(str);
	return ret;
}

cell* cell_bool(bool b) {
	cell* ret = cell_new(cell_bool_T);
	ret->u.bool_ = b;
	return ret;
}

cell* cell_symbol(char* str) {
	cell* ret = cell_new(cell_symbol_T);
	ret->u.str = str;
	return ret;
}

cell* cell_list(int count, ...) {
	va_list ap;
	va_start(ap, count);
	assert(count <= 16);
	cell* ret = cell_new(cell_list_T);
	ret->u.vec = vector_new();
	if(count < 0) {
		count = 16;
	}
	for(int i=0; i<count; i++) {
		cell* e = va_arg(ap, cell*);
		if(count < 0 && e == NULL) { break; }
		vector_push(ret->u.vec, e);
	}
	va_end(ap);
	return ret;
}

cell* cell_call(const char* name, ...) {
	va_list ap;
	va_start(ap, name);
	cell* ret = cell_new(cell_call_T);
	cell_append(ret, cell_symbol(name));
	for(;;) {
		cell* e = va_arg(ap, cell*);
		if(e == NULL) { break; }
		cell_append(ret, e);
	}
	va_end(ap);
	return ret;
}

cell* cell_at(cell* self, int index) {
	assert(self->tag == cell_call_T);
	return (cell*)vector_at(self->u.vec, index);
}

cell* cell_eval(cell* code, tree_map* ctx) {
	assert(ctx != NULL);
	//アトムはそのまま返す
	if(cell_atom(code)) {
		return code;
	}
	//関数呼び出しなら
	if(code->tag == cell_call_T) {
		//シンボルを検索
		char* name = cell_2str(cell_at(code, 0));
		symbol* s = cell_find_symbol(name, ctx);
		if(s->tag == symbol_function_T) {
			return symbol_function_apply(s->u.func, code, ctx);
		}
	//シンボルなら
	} else if(code->tag == cell_symbol_T) {
		//シンボルを検索
		char* name = cell_2str(code);
		symbol* s = cell_find_symbol(name, ctx);
		if(s->tag == symbol_variable_T) {
			return cell_eval(s->u.code, ctx);
		}
	}
	assert(false);
}

symbol* cell_find_symbol(const char* name, tree_map* ctx) {
	symbol* s = cell_symbol_key(name);
	if(s == NULL && ctx != NULL) {
		s = (symbol*)tree_map_get(ctx, name);
	}
	return s;
}

int cell_2int(cell* self) {
	assert(self->tag == cell_int_T);
	return self->u.int_;
}

double cell_2double(cell* self) {
	assert(self->tag == cell_double_T);
	return self->u.double_;
}

char cell_2char(cell* self) {
	assert(self->tag == cell_char_T);
	return self->u.char_;
}

char* cell_2str(cell* self) {
	assert(self->tag == cell_string_T || self->tag == cell_symbol_T);
	return self->u.str;
}

bool cell_atom(cell* self) {
	return self->tag == cell_int_T ||
	       self->tag == cell_double_T ||
		   self->tag == cell_char_T ||
		   self->tag == cell_string_T;
}

void cell_append(cell* self, cell* a) {
	assert(self->tag == cell_call_T);
	vector_push(self->u.vec, a);
}

int cell_fprintf(FILE* fp, cell* c) {
	switch(c->tag) {
		case cell_int_T:return fprintf(fp, "%d", c->u.int_);
		case cell_double_T: return fprintf(fp, "%lf", c->u.double_);
		case cell_char_T: return fprintf(fp, "%c", c->u.char_);
		case cell_string_T: return fprintf(fp, "%s", c->u.str);
		case cell_symbol_T: return fprintf(fp, ":%s", c->u.str);
		case cell_bool_T: return fprintf(fp, c->u.bool_ ? "TRUE" : "FALSE");
		case cell_call_T:
		{
			cell* name = cell_at(c, 0);
			fprintf(fp, "(%s", name->u.str);
			for(int i=1; i<c->u.vec->length; i++) {
				fprintf(fp, " ");
				cell_fprintf(fp, cell_at(c, i));
			}
			fprintf(fp, ")");
			break;
		}
	}
	return -1;
}

void cell_debug(cell* self) {
	cell_fprintf(stdout, self);
	text_putline();
//	cell_delete(self);
}

void cell_delete(cell* self) {
	if(self == NULL) {
		return;
	}
	if(self->tag == cell_string_T) {
		MEM_FREE(self->u.str);
	} else if(self->tag == cell_call_T) {
		vector_delete(self->u.vec, cell_cell_delete);
	}
	MEM_FREE(self);
}

void cell_symbol_allocate() {
	if(gVec == NULL) { gVec = vector_new(); }
	if(gHeap == NULL) { gHeap = vector_new(); }
	if(gMap == NULL) {
		gMap = tree_map_new();
		cell_define_function_builtin("print", blt_print);
		cell_define_function_builtin("println", blt_println);
		cell_define_function_builtin("+", blt_add);
		cell_define_function_builtin("-", blt_sub);
		cell_define_function_builtin("*", blt_mul);
		cell_define_function_builtin("/", blt_div);
		cell_define_function_builtin("%", blt_mod);

		cell_define_function_builtin(">", blt_gt);
		cell_define_function_builtin(">=", blt_ge);
		cell_define_function_builtin("<", blt_lt);
		cell_define_function_builtin("<=", blt_le);
		cell_define_function_builtin("eval", blt_eval);
		cell_define_function_builtin("progn", blt_progn);
		cell_define_function_builtin("defun", blt_defun);
		cell_define_function_builtin("defvar", blt_defvar);
		cell_define_function_builtin("let", blt_let);
	}
}

int cell_symbol_intern(const char* name, symbol* s) {
	assert(gVec != NULL);
	assert(gMap != NULL);
	tree_item ret = tree_map_get(gMap, name);
	if(ret != NULL) {
		return (int)ret;
	}
	vector_push(gVec, s);
	tree_map_put(gMap, name, gVec->length);
	return gVec->length;
}

symbol* cell_symbol_id(int id) {
	return (symbol*)vector_at(gVec, id);
}

symbol* cell_symbol_key(const char* key) {
	int index = (int)tree_map_get(gMap, key) - 1;
	if(index < 0) return NULL;
	return (symbol*)vector_at(gVec, index);
}

void cell_define_function_builtin(const char* name, cell_apply a) {
	symbol* ret = symbol_new(symbol_function_T);
	ret->u.func = symbol_function_new_builtin(a);
	cell_symbol_intern(name, ret);
}

void cell_define_function_user(const char* name, cell* params, cell* code) {
	symbol* ret = symbol_new(symbol_function_T);
	ret->u.func = symbol_function_new_user(params, code);
	cell_symbol_intern(name, ret);
}

void cell_define_variable(const char* name, cell* value) {
	symbol* ret = symbol_new(symbol_variable_T);
	ret->u.code = value;
	cell_symbol_intern(name, ret);
}

void cell_symbol_destroy() {
	tree_map_delete(gMap, tree_map_deleter_null);
	vector_delete(gVec, cell_symbol_delete);
	vector_delete(gHeap, cell_cell_delete);
	gMap = NULL;
	gVec = NULL;
	gHeap = NULL;
}

//private
static void cell_cell_delete(vector_item item) {
	cell* e = (cell*)item;
	cell_delete(e);
}

static void cell_symbol_delete(vector_item item) {
	symbol* e = (symbol*)item;
	symbol_delete(e);
}

//blt
static cell* blt_print(vector* args, tree_map* ctx) {
	args_check(args, 1);
	cell* a = args_at(args, 0);
	cell_fprintf(stdout, a);
	return CELL_VOID;
}

static cell* blt_println(vector* args, tree_map* ctx) {
	args_check(args, 1);
	cell* a = args_at(args, 0);
	cell_fprintf(stdout, a);
	text_putline();
	return CELL_VOID;
}

static cell* blt_add(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_int(cell_2int(a) + cell_2int(b));
}

static cell* blt_sub(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_int(cell_2int(a) - cell_2int(b));
}

static cell* blt_mul(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_int(cell_2int(a) * cell_2int(b));
}

static cell* blt_div(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_int(cell_2int(a) / cell_2int(b));
}

static cell* blt_mod(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_int(cell_2int(a) % cell_2int(b));
}

static cell* blt_gt(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_bool(cell_2int(a) > cell_2int(b));
}

static cell* blt_ge(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_bool(cell_2int(a) >= cell_2int(b));
}

static cell* blt_lt(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_bool(cell_2int(a) < cell_2int(b));
}

static cell* blt_le(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* a = args_at(args, 0);
	cell* b = args_at(args, 1);
	return cell_bool(cell_2int(a) <= cell_2int(b));
}

static cell* blt_eval(vector* args, tree_map* ctx) {
	args_check(args, 1);
	return cell_eval(args_at(args, 0), ctx);
}

static cell* blt_progn(vector* args, tree_map* ctx) {
	cell* ret = NULL;
	for(int i=1; i<args->length; i++) {
		cell* e = (cell*)vector_at(args, i);
		if(e == NULL) { break; }
		ret = cell_eval(e, ctx);
	}
	return ret;
}

static cell* blt_defun(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* cname = args_at(args, 0);
	cell* params = args_at(args, 1);
	cell* code = args_at(args, 2);
	cell_define_function_user(cell_2str(cname), params, code);
	return CELL_VOID;
}

static cell* blt_defvar(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* cname = args_at(args, 0);
	cell* code = args_at(args, 1);
	char* name = cell_2str(cname);
	cell_define_variable(name, code);
	return code;
}

static cell* blt_let(vector* args, tree_map* ctx) {
	args_check(args, 2);
	cell* cname = args_at(args, 0);
	cell* code = args_at(args, 1);
	char* name = cell_2str(cname);
	if(ctx == NULL) {
		cell_define_variable(name, code);
	} else {
		symbol* s = symbol_new(symbol_variable_T);
		s->u.code = code;
		tree_map_put(ctx, name, s);
	}
	return code;
}
