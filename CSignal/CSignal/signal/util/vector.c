#include "vector.h"
#include <assert.h>
#include "mem.h"

#define SLOT_SIZE sizeof(void*)

vector * vector_new() {
	vector* ret = (vector*)MEM_MALLOC(sizeof(vector));
	ret->length = 0;
	ret->capacity = 16;
	ret->memory = (vector_item*)MEM_MALLOC(SLOT_SIZE * 16);
	return ret;
}

void vector_push(vector * self, vector_item item) {
	assert(self != NULL);
	if (self->length >= self->capacity) {
		vector_reserve(self);
		self->memory[self->length] = item;
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
	assert(self->length > 0);
	vector_item ret = self->memory[self->length - 1];
	//二重に開放しないように
	self->memory[self->length - 1] = NULL;
	self->length--;
	return ret;
}

void vector_insert(vector * self, int index, vector_item item) {
	assert(index >= 0 && index < (self->length + 1));
	if (self->capacity < (self->length + 1)) {
		vector_reserve(self);
	}
	vector_item t = self->memory[index];
	for (int i = index; i < self->length; i++) {
		vector_item b = self->memory[i + 1];
		self->memory[i + 1] = t;
		t = b;
	}
	self->memory[index] = item;
	self->length++;
}

int vector_reserve(vector * self) {
	int newCapacitySize = self->capacity + (self->capacity / 2);
	vector_item* temp = (vector_item*)MEM_REALLOC(self->memory, SLOT_SIZE * newCapacitySize);
	assert(temp != NULL);
	self->memory = temp;
	self->capacity = newCapacitySize;
	return newCapacitySize;
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

void vector_clear(vector * self) {
	while (self->length > 0) {
		vector_pop(self);
	}
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
	MEM_FREE(self->memory);
	MEM_FREE(self);
}

void vector_deleter_free(vector_item item) {
	MEM_FREE(item);
}

void vector_deleter_null(vector_item item) {
}

#undef SLOT_SIZE