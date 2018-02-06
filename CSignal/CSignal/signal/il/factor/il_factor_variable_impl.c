#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../util/mem.h"
#include "../../vm/symbol_entry.h"

//proto
static void il_factor_variable_check(il_factor_variable* self, enviroment* env);

il_factor * il_factor_wrap_variable(il_factor_variable * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_variable;
	ret->u.variable_ = self;
	return ret;
}

il_factor_variable * il_factor_variable_new(const char * name) {
	il_factor_variable* ret = (il_factor_variable*)MEM_MALLOC(sizeof(il_factor_variable));
	ret->name = text_strdup(name);
	ret->index = -1;
	ret->type = NULL;
	return ret;
}

void il_factor_variable_dump(il_factor_variable * self, int depth) {
	text_putindent(depth);
	text_printf("variable %s", self->name);
	text_putline();
}

void il_factor_variable_generate(il_factor_variable * self, enviroment* env) {
	il_factor_variable_check(self, env);
	opcode_buf_add(env->buf, op_load);
	opcode_buf_add(env->buf, self->index);
}

void il_factor_variable_load(il_factor_variable * self, enviroment * env, il_ehandler * eh) {
	il_factor_variable_check(self, env);
}

type * il_factor_variable_eval(il_factor_variable * self, enviroment * env) {
	il_factor_variable_check(self, env);
	return self->type;
}

void il_factor_variable_delete(il_factor_variable * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_factor_variable_check(il_factor_variable* self, enviroment* env) {
	if (self->index != -1) {
		return;
	}
	symbol_entry* e = symbol_table_entry(
		env->sym_table, 
		NULL,
		self->name
	);
	self->type = e->type;
	self->index = e->index;
}