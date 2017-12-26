#include "vector.h"
#include <assert.h>

#define SLOT_SIZE sizeof(void*)

vector * vector_new() {
	vector* ret = (vector*)malloc(sizeof(vector));
	ret->length = 0;
	ret->capacity = 16;
	ret->memory = (vector_item*)malloc(SLOT_SIZE * 16);
	return ret;
}

void vector_push(vector * self, vector_item item) {
	assert(self != NULL);
	if (self->length >= self->capacity) {
		int newCapacitySize = self->capacity + (self->capacity / 2);
		vector_item* temp = (vector_item*)realloc(self->memory, SLOT_SIZE * newCapacitySize);
		assert(temp != NULL);
		self->memory = temp;
		self->memory[self->length] = item;
		self->capacity = newCapacitySize;
	} else {
		self->memory[self->length] = item;
	}
	self->length++;
}

vector_item vector_top(vector * self) {
	assert(self != NULL);
//	return self->memory[self->length];
	return *(self->memory + (self->length - 1));
}

vector_item vector_pop(vector * self) {
	assert(self != NULL);
	vector_item ret = self->memory[self->length - 1];
	//二重に開放しないように
	self->memory[self->length - 1] = NULL;
	self->length--;
	return ret;
}

void vector_assign(vector * self, int index, vector_item item) {
	assert(index >= 0);
	//伸ばす必要がない
	if (index < self->length) {
		self->memory[index] = item;
	} else {
		while (self->length <= index) {
			vector_push(self, NULL);
		}
		vector_assign(self, index, item);
	}
}

vector_item vector_at(vector * self, int index) {
	assert(index >= 0 && index < self->length);
	return self->memory[index];
//	return *(self->memory + index);
}

void vector_delete(vector * self, vector_element_deleter deleter) {
	if (self == NULL) {
		return;
	}
	for (int i = 0; i < self->length; i++) {
		vector_item e = self->memory[i];
		self->memory[i] = NULL;
		deleter(e);
	}
	free(self->memory);
	free(self);
}

void vector_deleter_free(vector_item item) {
	free(item);
}

void vector_deleter_null(vector_item item) {
}

#undef SLOT_SIZE