#include "method.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"
#include "parameter.h"
#include "parameter_list.h"

method * method_new(const char * name) {
	method* ret = (method*)malloc(sizeof(method));
	ret->name = text_strdup(name);
	ret->parameter_list = parameter_list_new();
	return ret;
}

void method_dump(method * self, int depth) {
	text_putindent(depth);
	printf("method %s", self->name);
	printf("(");
	parameter_list* pointee = self->parameter_list;
	while (1) {
		parameter* param = (parameter*)pointee->item;
		printf("%s", param->name);
		pointee = pointee->next;
		if (pointee == NULL || pointee->item == NULL) {
			break;
		} else printf(" ");
	}
	printf(")");
	text_putline();
}

void method_delete(method * self) {
	free(self->name);
	parameter_list_delete(self->parameter_list);
	free(self);
}
