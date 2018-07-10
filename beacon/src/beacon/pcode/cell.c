#include "cell.h"
#include "symbol_interface.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/tree_map.h"
#include "../util/vector.h"
#include <assert.h>
#include <string.h>
#include <ctype.h>

static int cell_fprintfImpl(FILE* fp, cell* a, int depth);
static void cell_indent(FILE* fp, int depth);
//static cell* cell_push(cell** out, cell* d, cell* a);
static void cell_symbol_delete(vector_item item);
static void cell_assert(bool condition, const char* fmt, ...);

static cell* blt_atomp(cell* args, tree_map* ctx);
static cell* blt_eq(cell* args, tree_map* ctx);
static cell* blt_car(cell* args, tree_map* ctx);
static cell* blt_cdr(cell* args, tree_map* ctx);
static cell* blt_cons(cell* args, tree_map* ctx);
static cell* blt_cond(cell* args, tree_map* ctx);
static cell* blt_or(cell* args, tree_map* ctx);
static cell* blt_and(cell* args, tree_map* ctx);
static cell* blt_eval(cell* args, tree_map* ctx);
static cell* blt_quote(cell* args, tree_map* ctx);

static cell* blt_add(cell* args, tree_map* ctx);
static cell* blt_sub(cell* args, tree_map* ctx);
static cell* blt_mul(cell* args, tree_map* ctx);
static cell* blt_div(cell* args, tree_map* ctx);
static cell* blt_mod(cell* args, tree_map* ctx);
static cell* blt_gt(cell* args, tree_map* ctx);
static cell* blt_ge(cell* args, tree_map* ctx);
static cell* blt_lt(cell* args, tree_map* ctx);
static cell* blt_le(cell* args, tree_map* ctx);
static cell* blt_defun(cell* args, tree_map* ctx);
static cell* blt_nilp(cell* args, tree_map* ctx);


static tree_map* gSymbolMap = NULL;
static vector* gSymbolVec = NULL;

cell* cell_malloc(cell_tag tag, const char* filename, int lineno) {
	cell* ret = (cell*)mem_malloc(sizeof(cell), filename, lineno);
	ret->tag = tag;
	ret->rest = NULL;
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

cell* cell_string(const char* str) {
	assert(str != NULL);
	cell* ret = cell_new(cell_string_T);
	ret->u.string_ = text_strdup(str);
	return ret;
}

cell* cell_function(const char* str) {
	return cell_identifier(str);
}

cell* cell_identifier(const char* str) {
	assert(str != NULL);
	cell* ret = cell_new(cell_symbol_T);
	ret->u.string_ = str;
	return ret;
}

cell* cell_bool(bool a) {
	cell* ret = cell_new(cell_bool_T);
	ret->u.bool_ = a;
	return ret;
}

cell* cell_true() {
	return cell_bool(true);
}

cell* cell_false() {
	return cell_bool(false);
}

cell* cell_nil() {
	return cell_new(cell_nil_T);
}

cell* cell_cons(cell* a, cell* b) {
	cell* ret = cell_new(cell_cons_T);
	ret->rest = b;
	ret->u.first = a;
	return ret;
}

cell* cell_list(int len, ...) {
	va_list ap;
	va_start(ap, len);
	//0未満の場合は nil が現れるまで
	if(len < 0) {
		cell* aret = NULL;
		for(int i=0; true; i++) {
			cell* e = va_arg(ap, cell*);
			if(e == NULL) { break; }
			aret = cell_append(aret, e);
		}
		va_end(ap);
		return aret;
	}
	//空の場合には nil を返す
	if(len == 0) {
		cell* blank = cell_nil();
		va_end(ap);
		return blank;
	}
	//全て連結して返す
	cell* ret = NULL;
	for(int i=0; i<len; i++) {
		cell* e = va_arg(ap, cell*);
		ret = cell_append(ret, e);
	}
	va_end(ap);
	return ret;
}

cell* cell_call(const char* name, ...) {
	va_list ap;
	va_start(ap, name);
	cell* ret = NULL;
	for(int i=0; ; i++) {
		cell* e = va_arg(ap, cell*);
		if(e == NULL) { break; }
		ret = cell_append(ret, e);
	}
	va_end(ap);
	return cell_cons(cell_function(name), ret);
}

cell* cell_append(cell* self, cell* a) {
	if(self == NULL) {
		self = cell_cons(a, NULL);
		return self;
	}
	cell* cur = self;
	while(true) {
		cell* pivot = cur;
		cur = cur->rest;
		if(cur == NULL) {
			pivot->rest = cell_cons(a, NULL);
			break;
		}
	}
	return self;
}

cell* cell_dup(cell* src) {
	if(src == NULL) {
		return NULL;
	}
	if(cell_atomp(src)) {
		cell* ret = cell_new(src->tag);
		switch(src->tag) {
			case cell_nil_T: break;
			case cell_bool_T:
				ret->u.bool_ = src->u.bool_;
				break;
			case cell_string_T:
				ret->u.string_ = text_strdup(src->u.string_);
				break;
			case cell_int_T:
				ret->u.int_ = src->u.int_;
				break;
			case cell_double_T:
				ret->u.double_ = src->u.double_;
				break;
			case cell_symbol_T:
				ret->u.string_ = src->u.string_;
				break;
			default: assert(false);
		}
		return ret;
	} else {
		cell* ret = cell_new(cell_cons_T);
		ret->rest = cell_dup(src->rest);
		ret->u.first = cell_dup(src->u.first);
		return ret;
	}
}

cell* cell_eval(cell* code) {
	return cell_scoped_eval(code, NULL);
}

cell* cell_scoped_eval(cell* code, tree_map* ctx) {
//	cell_fprintf(stdout, code);
//	printf("\n");
	//末端ならNULL
	if(code == NULL) {
		return cell_nil();
	}
	//アトムはそのまま
	if(cell_atomp(code)) {
		return code;
	}
	//シンボルなら名前表を検索する
	if(code->u.first->tag == cell_symbol_T) {
		cell* first = code->u.first;
		symbol* s = cell_symbol_key(first->u.string_);
		text_printf("ref: %s\n", first->u.string_);
		//シンボルが見つからないなら環境から検索する
		if(s == NULL && ctx != NULL) {
			s = (symbol*)tree_map_get(ctx, first->u.string_);
		}
		//シンボルには関数か値
		if(s->tag == symbol_function_T) {
			return symbol_function_call(s, code->rest, ctx);
		} else if(s->tag == symbol_variable_T) {
			return cell_scoped_eval(s->u.var, ctx);
		}
		assert(false);
	}
	return code;
}

cell* cell_at(cell* code, int index) {
	cell* a = code;
	for(int i=0; i<index; i++) {
		a = a->rest;
	}
	return a->u.first;
}

bool cell_numberp(cell* self) {
	return self->tag == cell_int_T || self->tag == cell_double_T;
}

bool cell_consp(cell* self) {
	return self->tag == cell_cons_T;
}

bool cell_atomp(cell* self) {
	return !cell_consp(self);
}

bool cell_eq(cell* a, cell* b) {
	if(cell_atomp(a) && cell_atomp(b)) {
		if(a->tag != b->tag) {
			return false;
		}
		switch(a->tag) {
			case cell_nil_T: return true;
			case cell_bool_T: return a->u.bool_ == b->u.bool_;
			case cell_string_T: return !strcmp(a->u.string_, b->u.string_);
			case cell_int_T: return a->u.int_ == b->u.int_;
			case cell_double_T: return a->u.double_ == b->u.double_;
			default: assert(false);
		}
	} else if(cell_consp(a) && cell_consp(b)) {
		return cell_eq(a->rest, b->rest) && cell_eq(a->u.first, b->u.first);
	} else {
		return false;
	}
}

bool cell_blank(cell* a) {
	return a == NULL || a->tag == cell_nil_T;
}

bool cell_2bool(cell* a) {
	assert(a->tag == cell_bool_T);
	return a->u.bool_;
}

const char* cell_2str(cell* a) {
	assert(a->tag == cell_string_T || a->tag == cell_symbol_T);
	return a->u.string_;
}

tree_map* cell_2map(cell* params, cell* args, tree_map* ctx) {
	tree_map* ret = tree_map_new();
	while(true) {
		cell* arg = cell_scoped_eval(args->u.first, ctx);
		symbol* s = symbol_variable(arg);
		tree_map_put(ret, cell_2str(params->u.first), s);
		text_printf("arg: %s  ", cell_2str(params->u.first));
		text_printf("val: ");
		cell_fprintf(stdout, arg);
		text_putline();
		params = params->rest;
		args = args->rest;
		//どちらかだけが null
		assert(!((params == NULL || args == NULL) && params != args));
		if(params == NULL && args == NULL) {
			break;
		}
	}
	return ret;
}

int cell_fprintf(FILE* fp, cell* a) {
	int ret = cell_fprintfImpl(fp, a, 0);
	return ret;
}

void cell_delete(cell* self) {
	if(self == NULL) { return; }
	cell_delete(self->rest);
	if(self->tag == cell_string_T) {
		MEM_FREE(self->u.string_);
	}
	MEM_FREE(self);
}

void cell_debug(cell* temp) {
	cell_fprintf(stdout, temp);
	fprintf(stdout, "\n");
	cell_delete(temp);
}

void cell_symbol_allocate() {
	if(gSymbolVec == NULL) {
		gSymbolVec = vector_new();
	}
	if(gSymbolMap == NULL) {
		gSymbolMap = tree_map_new();
		cell_symbol_intern("atomp", symbol_function_c(blt_atomp));
		cell_symbol_intern("eq", symbol_function_c(blt_eq));
		cell_symbol_intern("car", symbol_function_c(blt_car));
		cell_symbol_intern("cdr", symbol_function_c(blt_cdr));
		cell_symbol_intern("cons", symbol_function_c(blt_cons));
		cell_symbol_intern("cond", symbol_function_c(blt_cond));
		cell_symbol_intern("or", symbol_function_c(blt_or));
		cell_symbol_intern("and", symbol_function_c(blt_and));
		cell_symbol_intern("eval", symbol_function_c(blt_eval));
		cell_symbol_intern("quote", symbol_function_c(blt_quote));
		cell_symbol_intern("defun", symbol_function_c(blt_defun));
		cell_symbol_intern("nilp", symbol_function_c(blt_nilp));
		cell_symbol_intern("'", symbol_function_c(blt_quote));

		cell_symbol_intern("+", symbol_function_c(blt_add));
		cell_symbol_intern("-", symbol_function_c(blt_sub));
		cell_symbol_intern("*", symbol_function_c(blt_mul));
		cell_symbol_intern("/", symbol_function_c(blt_div));
		cell_symbol_intern("%", symbol_function_c(blt_mod));

		cell_symbol_intern(">", symbol_function_c(blt_gt));
		cell_symbol_intern(">=", symbol_function_c(blt_ge));
		cell_symbol_intern("<", symbol_function_c(blt_lt));
		cell_symbol_intern("<=", symbol_function_c(blt_le));
	}
}

void cell_symbol_destroy() {
	//名前表の破棄
	tree_map_delete(gSymbolMap, tree_map_deleter_null);
	gSymbolMap = NULL;
	//シンボルの破棄
	vector_delete(gSymbolVec, cell_symbol_delete);
	gSymbolVec = NULL;
}

int cell_symbol_intern(const char* name, symbol* s) {
	assert(name != NULL);
	assert(s != NULL);
	int id = (int)tree_map_get(gSymbolMap, name);
	if(id > 0) {
		return id;
	}
	vector_push(gSymbolVec, s);
	tree_map_put(gSymbolMap, name, (tree_item)gSymbolVec->length);
	return gSymbolVec->length;
}

symbol* cell_symbol_id(int id) {
	id = id - 1;
	assert(id >= 0);
	return (symbol*)vector_at(gSymbolVec, id);
}

symbol* cell_symbol_key(const char* name) {
	return (symbol*)vector_at(gSymbolVec, ((int)tree_map_get(gSymbolMap, name)) - 1);
}

//private
static int cell_fprintfImpl(FILE* fp, cell* a, int depth) {
	if(a == NULL) {
		return fprintf(fp, "nil");
	}
	if(a->tag == cell_cons_T) {
		fprintf(fp, "(");
		cell_fprintfImpl(fp, a->u.first, depth + 1);
		fprintf(fp, " ");
		cell_fprintfImpl(fp, a->rest, depth + 1);
		fprintf(fp, ")");
		return 0;
	} else if(a->tag == cell_nil_T) {
		return fprintf(fp, "nil");
	} else if(a->tag == cell_int_T) {
		return fprintf(fp, "%d", a->u.int_);
	} else if(a->tag == cell_double_T) {
		return fprintf(fp, "%lf", a->u.double_);
	} else if(a->tag == cell_bool_T) {
		return fprintf(fp, a->u.bool_ ? "true" : "false");
	} else if(a->tag == cell_string_T) {
		return fprintf(fp, "\"%s\"", a->u.string_);
	} else if(a->tag == cell_symbol_T) {
		return fprintf(fp, "`%s", a->u.string_);
	}
	return -1;
}

static void cell_indent(FILE* fp, int depth) {
	for(int i=0; i<depth; i++) {
		fprintf(fp, "    ");
	}
}

static void cell_symbol_delete(vector_item item) {
	symbol* e = (symbol*)item;
	symbol_delete(e);
}

static void cell_assert(bool condition, const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
	assert(condition);
	va_end(ap);
}
//blt
static cell* blt_atomp(cell* args, tree_map* ctx) {
	return cell_bool(cell_atomp(cell_at(args, 0)));
}

static cell* blt_eq(cell* args, tree_map* ctx) {
	return cell_bool(cell_eq(cell_at(args, 0), cell_at(args, 1)));
}

static cell* blt_car(cell* args, tree_map* ctx) {
	return cell_at(args, 0)->u.first;
}

static cell* blt_cdr(cell* args, tree_map* ctx) {
	return cell_at(args, 0)->rest;
}

static cell* blt_cons(cell* args, tree_map* ctx) {
	return cell_cons(cell_at(args, 0), cell_at(args, 1));
}

static cell* blt_cond(cell* args, tree_map* ctx) {
	cell* c0 = cell_at(args, 0);
	cell* c1 = cell_at(args, 1);
	cell* c2 = cell_at(args, 2);
	bool wh = cell_2bool(cell_eval(c0));
	return cell_scoped_eval(wh ? c1 : c2, ctx);
}

static cell* blt_or(cell* args, tree_map* ctx) {
	return cell_bool(cell_2bool(cell_at(args, 0)) || cell_2bool(cell_at(args, 1)));
}

static cell* blt_and(cell* args, tree_map* ctx) {
	return cell_bool(cell_2bool(cell_at(args, 0)) && cell_2bool(cell_at(args, 1)));
}

static cell* blt_eval(cell* args, tree_map* ctx) {
	return cell_scoped_eval(cell_at(args, 0), ctx);
}

static cell* blt_quote(cell* args, tree_map* ctx) {
	cell* ret = cell_at(args, 0);
	return ret;
}

static cell* blt_add(cell* args, tree_map* ctx) {
	cell* a = eval_at(args, 0, ctx);
	cell* b = eval_at(args, 1, ctx);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_int(a->u.int_ + b->u.int_);
	} else if(a->tag) {
		return cell_double(a->u.double_ + b->u.double_);
	}
	return cell_nil();
}

static cell* blt_sub(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_int(a->u.int_ - b->u.int_);
	} else if(a->tag) {
		return cell_double(a->u.double_ - b->u.double_);
	}
	return cell_nil();
}

static cell* blt_mul(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_int(a->u.int_ * b->u.int_);
	} else if(a->tag) {
		return cell_double(a->u.double_ * b->u.double_);
	}
	return cell_nil();
}

static cell* blt_div(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_int(a->u.int_ / b->u.int_);
	} else if(a->tag) {
		return cell_double(a->u.double_ / b->u.double_);
	}
	return cell_nil();
}

static cell* blt_mod(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_int(a->u.int_ % b->u.int_);
	} else if(a->tag) {
		return cell_double((int)a->u.double_ % (int)b->u.double_);
	}
	return cell_nil();
}

static cell* blt_gt(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_bool(a->u.int_ > b->u.int_);
	} else if(a->tag) {
		return cell_bool(a->u.double_ > b->u.double_);
	}
	return cell_nil();
}

static cell* blt_ge(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_bool(a->u.int_ >= b->u.int_);
	} else if(a->tag) {
		return cell_bool(a->u.double_ >= b->u.double_);
	}
	return cell_nil();
}

static cell* blt_lt(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_bool(a->u.int_ < b->u.int_);
	} else if(a->tag) {
		return cell_bool(a->u.double_ < b->u.double_);
	}
	return cell_nil();
}

static cell* blt_le(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	cell* b = cell_at(args, 1);
	assert(cell_numberp(a) && cell_numberp(b));
	if(a->tag != b->tag) {
		return cell_nil();
	}
	if(a->tag == cell_int_T) {
		return cell_bool(a->u.int_ <= b->u.int_);
	} else if(a->tag) {
		return cell_bool(a->u.double_ <= b->u.double_);
	}
	return cell_nil();
}

static cell* blt_defun(cell* args, tree_map* ctx) {
	cell* clone = cell_dup(args);
	cell* c0 = cell_at(clone, 0);
	cell* c1 = cell_at(clone, 1);
	cell* c2 = cell_at(clone, 2);
	const char* name = cell_2str(c0);
	cell_symbol_intern(name, symbol_function_lisp(clone));
	return clone;
}

static cell* blt_nilp(cell* args, tree_map* ctx) {
	cell* a = cell_at(args, 0);
	bool b = a == NULL || a->tag == cell_nil_T;
	return cell_bool(b);
}