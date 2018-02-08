#include "il_factor_dec_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"

il_factor * il_factor_wrap_dec(il_factor_dec * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_dec;
	ret->u.dec_ = self;
	return ret;
}

il_factor_dec * il_factor_dec_new(fix_type type) {
	il_factor_dec* ret = (il_factor_dec*)MEM_MALLOC(sizeof(il_factor_dec));
	ret->type = type;
	ret->fact = NULL;
	return ret;
}

void il_factor_dec_dump(il_factor_dec * self, int depth) {
	text_putindent(depth);
	text_printf("--");
	text_putline();
	il_factor_dump(self->fact, depth + 1);
}

void il_factor_dec_generate(il_factor_dec * self, enviroment * env) {
	il_factor_generate(self->fact, env);
}

void il_factor_dec_load(il_factor_dec * self, enviroment * env, il_ehandler * eh) {
	il_factor_load(self->fact, env, eh);
}

type * il_factor_dec_eval(il_factor_dec * self, enviroment * env) {
	return il_factor_eval(self->fact, env);
}

void il_factor_dec_delete(il_factor_dec * self) {
	il_factor_delete(self->fact);
	MEM_FREE(self);
}
