#include "il_class_list.h"
#include <stdlib.h>

il_class_list* il_class_list_new() {
	il_class_list* ret = (il_class_list*)malloc(sizeof(il_class_list));
	ret->classz = NULL;
	ret->next = NULL;
	return ret;
}

void il_class_list_push(il_class_list* self, il_class* classz) {
	if(self->classz == NULL) {
		self->classz = classz;
	} else {
		if(self->next == NULL) {
			self->next = il_class_list_new();
			il_class_list_push(self->next, classz);
		} else {
			il_class_list_push(self->next, classz);
		}
	}
}

void il_class_list_delete(il_class_list* self) {
	if(self == NULL) {
		return;
	}
	il_class_list* pointee = self;
	while(1) {
		il_class_delete(pointee->classz);
		if(pointee->next == NULL) {
			free(pointee);
			break;
		}
		il_class_list* temp = pointee;
		pointee = pointee->next;
		free(temp);
	}
}