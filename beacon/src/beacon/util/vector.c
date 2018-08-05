#include "vector.h"
#include <assert.h>
#include "mem.h"

#define SLOT_SIZE sizeof(void*)

vector* vector_malloc(const char* filename, int lineno) {
	vector* ret = (vector*)mem_malloc(sizeof(vector), filename, lineno);
	ret->length = 0;
	ret->capacity = 16;
	ret->memory = (vector_item*)mem_malloc(SLOT_SIZE * 16, filename, lineno);
	return ret;
}

void vector_push(vector * self, vector_item item) {
	assert(self != NULL);
	if (self->length >= self->capacity) {
		vector_reserve(self);
	}
	self->memory[self->length] = item;
	self->length++;
}

vector* vector_append(vector* self, vector_item item) {
	if(self == NULL) {
		self = vector_new();
	}
	vector_push(self, item);
	return self;
}

vector_item vector_top(vector * self) {
	assert(self != NULL);
	assert(self->length > 0);
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

vector_item vector_remove(vector * self, int index) {
	assert(index >= 0 && index < self->length);
	vector_item ret = self->memory[index];
	for (int i = index + 1; i < self->length; i++) {
		self->memory[i - 1] = self->memory[i];
	}
	self->length--;
	return ret;
}

void vector_pack(vector* self) {
	assert(self != NULL);
	self->memory = MEM_REALLOC(self->memory, SLOT_SIZE * self->length);
	self->capacity = self->length;
}

int vector_reserve(vector * self) {
	assert(self->capacity > 0);
	int newCapacitySize = self->capacity + (self->capacity / 2);
	vector_item* temp = MEM_REALLOC(self->memory, SLOT_SIZE * newCapacitySize);
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
}

vector* vector_sub(vector* self, int offset, int len) {
	assert(offset >= 0);
	if(len == 0) {
		return vector_new();
	}
	vector* v = vector_new();
	for(int i=offset; i<offset+len; i++) {
		vector_push(v, vector_at(self, i));
	}
	return v;
}

bool vector_empty(vector * self) {
	return self->length == 0;
}

int vector_find(vector * self, vector_item item) {
	int pos = -1;
	for (int i = 0; i < self->length; i++) {
		vector_item e = vector_at(self, i);
		if (e == item) {
			pos = i;
			break;
		}
	}
	return pos;
}

bool vector_contains(vector * self, vector_item item) {
	return vector_find(self, item);
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
	//vector_pack(self);
	for (int i = 0; i < self->length; i++) {
		vector_item e = self->memory[i];
		self->memory[i] = NULL;
		deleter(e);
	}
	MEM_FREE(self->memory);
	self->memory = NULL;
	MEM_FREE(self);
}

void vector_deleter_free(vector_item item) {
	MEM_FREE(item);
}

void vector_deleter_null(vector_item item) {
}

vector* vector_clone(vector* source) {
	vector* ret = vector_new();
	for(int i=0; i<source->length; i++) {
		vector_push(ret, vector_at(source, i));
	}
	return ret;
}

void vector_each(vector* self, vector_action a) {
	for(int i=0; i<self->length; i++) {
		a(vector_at(self, i));
	}
}
#undef SLOT_SIZE