#include "il_stmt_try_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include <stdio.h>

//proto
static void il_stmt_catch_stmt_delete(void* item);
static void il_stmt_try_catch_delete(void* item);

il_stmt* il_stmt_wrap_try(il_stmt_try* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->type = ilstmt_try;
	ret->u.try_ = self;
	return ret;
}

il_stmt_try* il_stmt_try_new() {
	il_stmt_try* ret = (il_stmt_try*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->statement_list = vector_new();
	ret->catch_list = vector_new();
	return ret;
}

il_stmt_catch* il_stmt_catch_new(const char* name) {
	il_stmt_catch* ret = (il_stmt_catch*)MEM_MALLOC(sizeof(il_stmt_catch));
	ret->name = text_strdup(name);
	ret->fqcn = fqcn_cache_new();
	ret->statement_list = vector_new();
	return ret;
}

void il_stmt_try_dump(il_stmt_try* self, int depth) {
	text_putindent(depth);
	printf("try");
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
	for(int i=0; i<self->catch_list->length; i++) {
		il_stmt_catch* e = (il_stmt_catch*)vector_at(self->catch_list, i);
		il_stmt_catch_dump(e, depth + 1);
	}
}

void il_stmt_catch_dump(il_stmt_catch* self, int depth) {
	text_putindent(depth);
	printf("catch(");
	fqcn_cache_print(self->fqcn);
	printf(" %s)", self->name);
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_stmt_try_generate(il_stmt_try* self, enviroment* env) {

}

void il_stmt_catch_generate(il_stmt_catch* self, enviroment* env) {

}

void il_stmt_try_load(il_stmt_try* self, enviroment* env, il_ehandler* eh) {

}

void il_stmt_catch_load(il_stmt_catch* self, enviroment* env, il_ehandler* eh) {

}

void il_stmt_catch_delete(il_stmt_catch* self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

void il_stmt_try_delete(il_stmt_try* self) {
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	vector_delete(self->catch_list, il_stmt_try_catch_delete);
	MEM_FREE(self);
}
//private
static void il_stmt_catch_stmt_delete(void* item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void il_stmt_try_catch_delete(void* item) {
	il_stmt_catch* e = (il_stmt_catch*)item;
	il_stmt_catch_delete(e);
}