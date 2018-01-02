#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "parameter.h"
#include "class.h"

constructor * constructor_new() {
	constructor* ret = (constructor*)MEM_MALLOC(sizeof(constructor));
	ret->parent = NULL;
	ret->env = NULL;
	ret->parameter_list = vector_new();
	ret->access = access_public;
	return ret;
}

void constructor_dump(constructor * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	printf(" constructor");
	printf("(");
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		parameter* p = (parameter*)e;
		printf("%s %s", p->classz->name, p->name);
		if ((i + 1) < self->parameter_list->length) {
			printf(" ");
		}
	}
	printf(")");
	text_putline();
	opcode_buf_dump(self->env->buf, depth + 1);
}

void constructor_delete(constructor * self) {
}
