#include "il_factor_static_invoke_impl.h"
#include "../il_argument.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <assert.h>

//proto
static void il_factor_static_invoke_delete_argument(vector_item item);

il_factor * il_factor_wrap_static_invoke(il_factor_static_invoke * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_static_invoke;
	ret->u.static_invoke_ = self;
	return ret;
}

il_factor_static_invoke * il_factor_static_invoke_new(const char* method_name) {
	il_factor_static_invoke* ret = (il_factor_static_invoke*)MEM_MALLOC(sizeof(il_factor_static_invoke));
	//ret->class_name = text_strdup(class_name);
	ret->method_name = text_strdup(method_name);
	ret->scope_vec = vector_new();
	ret->argument_list = vector_new();
	return ret;
}

void il_factor_static_invoke_dump(il_factor_static_invoke * self, int depth) {
	text_putindent(depth);
	printf("static invoke %s", self->method_name);
	text_putline();
	//X::C.call() のような呼び出しなら
	if (self->scope_vec->length > 0) {
		text_putindent(depth + 1);
		printf("scope");
		text_putline();
		for (int i = 0; i < self->scope_vec->length; i++) {
			char* e = (char*)vector_at(self->scope_vec, i);
			text_putindent(depth + 2);
			printf("%s", e);
			text_putline();
		}
	}
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_static_invoke_generate(il_factor_static_invoke * self, enviroment * env) {
}

class_ * il_factor_static_invoke_eval(il_factor_static_invoke * self, enviroment * env) {
	return NULL;
}

void il_factor_static_invoke_delete(il_factor_static_invoke * self) {
	//MEM_FREE(self->fqcn);
	assert(self->class_name != NULL);
	MEM_FREE(self->class_name);
	MEM_FREE(self->method_name);
	vector_delete(self->scope_vec, vector_deleter_free);
	vector_delete(self->argument_list, il_factor_static_invoke_delete_argument);
	MEM_FREE(self);
}


//private
static void il_factor_static_invoke_delete_argument(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}