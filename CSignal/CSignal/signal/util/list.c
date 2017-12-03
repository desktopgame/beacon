#include "list.h"
#include <stdlib.h>
#include <assert.h>

list * list_new() {
	list* li = (list*)malloc(sizeof(list));
	li->item = NULL;
	li->prev = NULL;
	li->next = NULL;
	return li;
}

list_item list_add(list * self, list_item item) {
	assert(self != NULL);
	if (self->item == NULL) {
		self->item = item;
		return item;
	}
	if (self->next == NULL) {
		list* nextElement = list_new();
		self->next = nextElement;
		nextElement->prev = self;
		nextElement->item = item;
	} else {
		return list_add(self->next, item);
	}
	return item;
}

list_item list_at(list * self, int index) {
	assert(self != NULL);
	assert(index >= 0);
	list* pointee = self;
	int offset = 0;
	while (1) {
		if (pointee == NULL) {
			//境界外アクセス
			break;
		}
		if (offset == index) {
			return pointee->item;
		}
		offset++;
		pointee = pointee->next;
	}
	return NULL;
}

void list_delete(list * self, list_element_deleter deleter) {
	assert(self != NULL);
	list* pointee = self;
	while (1) {
		list* next = pointee->next;
		pointee->next = NULL;
		if (next) {
			next->prev = NULL;
		}
		list_item item = pointee->item;
		pointee->item = NULL;
		if (item) {
			deleter(item);
		}
		free(pointee);
		pointee = next;
		if (!next) {
			break;
		}
	}
}

void list_deleter_free(list_item item) {
	free(item);
}

void list_deleter_null(list_item item) {
}
