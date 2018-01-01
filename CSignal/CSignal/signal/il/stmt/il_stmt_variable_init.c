#include "il_stmt_variable_init.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

il_stmt * il_stmt_wrap_variable_init(il_stmt_variable_init * self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->type = ilstmt_variable_init;
	ret->u.variable_init = self;
	return ret;
}

il_stmt_variable_init * il_stmt_variable_init_new(const char * name) {
	il_stmt_variable_init* ret = (il_stmt_variable_init*)MEM_MALLOC(sizeof(il_stmt_variable_init));
	ret->name = text_strdup(name);
	ret->fact = NULL;
	ret->fqcn = fqcn_cache_new();
	return ret;
}

void il_stmt_variable_init_dump(il_stmt_variable_init * self, int depth) {
	text_putindent(depth);
	printf("variable init %s", self->name);
	text_putline();
	fqcn_cache_dump(self->fqcn, depth + 1);
	il_factor_dump(self->fact, depth + 1);
}

void il_stmt_variable_init_generate(il_stmt_variable_init * self, enviroment * env) {
}

void il_stmt_variable_init_delete(il_stmt_variable_init * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}
