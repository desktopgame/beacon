#include "il_import_list.h"
#include <stdlib.h>

il_import_list* il_import_list_new() {
	il_import_list* ret = (il_import_list*)malloc(sizeof(il_import_list));
	ret->import = NULL;
	ret->next = NULL;
	return ret;
}

void il_import_list_push(il_import_list* self, il_import* child) {
	if(self->import == NULL) {
		self->import = child;
	} else {
		if(self->next == NULL) {
			self->next = il_import_list_new();
			il_import_list_push(self->next, child);
		} else {
			il_import_list_push(self->next, child);
		}
	}
}

void il_import_list_delete(il_import_list* self) {
	if(self == NULL) {
		return;
	}
	il_import_list* pointee = self;
	while(1) {
		il_import_delete(pointee->import);
		if(pointee->next == NULL) {
			free(pointee);
			break;
		}
		il_import_list* temp = pointee;
		pointee = pointee->next;
		free(temp);
	}
}