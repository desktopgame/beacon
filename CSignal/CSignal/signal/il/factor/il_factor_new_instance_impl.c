#include "il_factor_new_instance_impl.h"
#include "../../util/mem.h"
#include "../il_argument.h"
#include "../../vm/enviroment.h"
#include "../../env/class.h"
#include "../../util/text.h"
#include <stdio.h>

il_factor * il_factor_wrap_new_instance(il_factor_new_instance * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_new_instance;
	ret->u.new_instance_ = self;
	return ret;
}

il_factor_new_instance * il_factor_new_instance_new() {
	il_factor_new_instance* ret = (il_factor_new_instance*)MEM_MALLOC(sizeof(il_factor_new_instance));
	ret->fqcn = fqcn_cache_new();
	ret->argument_list = vector_new();
	return ret;
}

void il_factor_new_instance_dump(il_factor_new_instance * self, int depth) {
	text_putindent(depth);
	printf("new instance");
	text_putline();

	fqcn_cache_dump(self->fqcn, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		il_argument* ilarg = (il_argument*)vector_at(self->argument_list, i);
		il_argument_dump(ilarg, depth + 1);
	}
}

void il_factor_new_instance_generate(il_factor_new_instance * self, enviroment * env) {
}

class_ * il_factor_new_instance_eval(il_factor_new_instance * self, enviroment * env) {
	return NULL;
}

void il_factor_new_instance_delete(il_factor_new_instance * self) {
}
