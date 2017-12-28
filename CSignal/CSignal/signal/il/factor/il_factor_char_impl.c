#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/class.h"

il_factor * il_factor_wrap_char(il_factor_char * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_cquote;
	ret->u.char_ = self;
	return ret;
}

il_factor_char * il_factor_char_new(char c) {
	il_factor_char* ret = (il_factor_char*)malloc(sizeof(il_factor_char));
	ret->value = c;
	return ret;
}

void il_factor_char_dump(il_factor_char * self, int depth) {
	text_putindent(depth);
	printf("Char %c", self->value);
	text_putline();
}

void il_factor_char_generate(il_factor_char * self, enviroment * env) {
	int index = enviroment_add_constant(env, self->value);
	opcode_buf_add(env->buf, op_constc);
	opcode_buf_add(env->buf, index);
}

class_ * il_factor_char_eval(il_factor_char * self, enviroment * env) {
	return CL_CHAR;
}

void il_factor_char_delete(il_factor_char * self) {
	free(self);
}
