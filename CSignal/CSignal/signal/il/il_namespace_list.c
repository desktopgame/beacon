#include "il_namespace_list.h"
#include <stdlib.h>
#include <assert.h>

il_namespace_list* il_namespace_list_new() {
	il_namespace_list* ret = (il_namespace_list*)malloc(sizeof(il_namespace_list));
	ret->namespacez = NULL;
	ret->next = NULL;
	return ret;
}

void il_namespace_list_push(il_namespace_list* self, il_namespace* namespacez) {
	assert(self != NULL);
	if(self->namespacez == NULL) {
		self->namespacez = namespacez;
	} else {
		if(self->next == NULL) {
			self->next = il_namespace_list_new();
			il_namespace_list_push(self->next, namespacez);
		} else {
			il_namespace_list_push(self->next, namespacez);
		}
	}
}

void il_namespace_list_dump(il_namespace_list* self, int depth) {
	text_putindent(depth);
	printf("namespace-list");
	text_putline();
	il_namespace_list* pointee = self;
	while(1) {
		if(pointee->namespacez == NULL) {
			break;
		}
		il_namespace_dump(pointee->namespacez, depth + 1);
		if(pointee->next == NULL) {
			break;
		}
		pointee = pointee->next;
	}
}

void il_namespace_list_delete(il_namespace_list* self) {
	if(self == NULL) {
		return;
	}
	il_namespace_list* pointee = self;
	while(1) {
		il_namespace_delete(pointee->namespacez);
		if(pointee->next == NULL) {
			free(pointee);
			break;
		}
		il_namespace_list* temp = pointee;
		pointee = pointee->next;
		free(temp);
	}
}