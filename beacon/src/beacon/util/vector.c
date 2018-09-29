#include "vector.h"
#include <assert.h>
#include "mem.h"

#define SLOT_SIZE sizeof(void*)

Vector* MallocVector(const char* filename, int lineno) {
	Vector* ret = (Vector*)mem_malloc(sizeof(Vector), filename, lineno);
	ret->length = 0;
	ret->capacity = 16;
	ret->memory = (VectorItem*)mem_malloc(SLOT_SIZE * 16, filename, lineno);
	return ret;
}

void PushVector(Vector * self, VectorItem item) {
	assert(self != NULL);
	if (self->length >= self->capacity) {
		ReserveVector(self);
	}
	self->memory[self->length] = item;
	self->length++;
}

Vector* AppendVector(Vector* self, VectorItem item) {
	if(self == NULL) {
		self = NewVector();
	}
	PushVector(self, item);
	return self;
}

VectorItem TopVector(Vector * self) {
	assert(self != NULL);
	assert(self->length > 0);
	return *(self->memory + (self->length - 1));
}

VectorItem PopVector(Vector * self) {
	assert(self != NULL);
	assert(self->length > 0);
	VectorItem ret = self->memory[self->length - 1];
	//二重に開放しないように
	self->memory[self->length - 1] = NULL;
	self->length--;
	return ret;
}

void InsertVector(Vector * self, int index, VectorItem item) {
	assert(index >= 0 && index < (self->length + 1));
	if (self->capacity < (self->length + 1)) {
		ReserveVector(self);
	}
	VectorItem t = self->memory[index];
	for (int i = index; i < self->length; i++) {
		VectorItem b = self->memory[i + 1];
		self->memory[i + 1] = t;
		t = b;
	}
	self->memory[index] = item;
	self->length++;
}

VectorItem RemoveVector(Vector * self, int index) {
	assert(index >= 0 && index < self->length);
	VectorItem ret = self->memory[index];
	for (int i = index + 1; i < self->length; i++) {
		self->memory[i - 1] = self->memory[i];
	}
	self->length--;
	return ret;
}

void PackVector(Vector* self) {
	assert(self != NULL);
	self->memory = MEM_REALLOC(self->memory, SLOT_SIZE * self->length);
	self->capacity = self->length;
}

int ReserveVector(Vector * self) {
	assert(self->capacity > 0);
	int newCapacitySize = self->capacity + (self->capacity / 2);
	VectorItem* temp = MEM_REALLOC(self->memory, SLOT_SIZE * newCapacitySize);
	assert(temp != NULL);
	self->memory = temp;
	self->capacity = newCapacitySize;
	return newCapacitySize;
}

void AssignVector(Vector * self, int index, VectorItem item) {
	assert(index >= 0);
	//伸ばす必要がない
	if (index < self->length) {
		self->memory[index] = item;
	} else {
		while (self->length <= index) {
			PushVector(self, NULL);
		}
		AssignVector(self, index, item);
	}
}

VectorItem AtVector(Vector * self, int index) {
	assert(index >= 0 && index < self->length);
	return self->memory[index];
}

Vector* SubVector(Vector* self, int offset, int len) {
	assert(offset >= 0);
	if(len == 0) {
		return NewVector();
	}
	Vector* v = NewVector();
	for(int i=offset; i<offset+len; i++) {
		PushVector(v, AtVector(self, i));
	}
	return v;
}

bool IsEmptyVector(Vector * self) {
	return self->length == 0;
}

int FindVector(Vector * self, VectorItem item) {
	int pos = -1;
	for (int i = 0; i < self->length; i++) {
		VectorItem e = AtVector(self, i);
		if (e == item) {
			pos = i;
			break;
		}
	}
	return pos;
}

bool IsContainsVector(Vector * self, VectorItem item) {
	return FindVector(self, item);
}

void ClearVector(Vector * self) {
	while (self->length > 0) {
		PopVector(self);
	}
}

void DeleteVector(Vector * self, VectorElementDeleter deleter) {
	if (self == NULL) {
		return;
	}
	//vector_pack(self);
	for (int i = 0; i < self->length; i++) {
		VectorItem e = self->memory[i];
		self->memory[i] = NULL;
		deleter(e);
	}
	MEM_FREE(self->memory);
	self->memory = NULL;
	MEM_FREE(self);
}

void VectorDeleterByFree(VectorItem item) {
	MEM_FREE(item);
}

void VectorDeleterOfNull(VectorItem item) {
}

Vector* CloneVector(Vector* source) {
	Vector* ret = NewVector();
	for(int i=0; i<source->length; i++) {
		PushVector(ret, AtVector(source, i));
	}
	return ret;
}

void CopyVector(Vector* src, Vector* dst) {
	assert(dst->length == 0);
	for(int i=0; i<src->length; i++) {
		PushVector(dst, AtVector(src, i));
	}
}

void EachVector(Vector* self, VectorAction a) {
	for(int i=0; i<self->length; i++) {
		a(AtVector(self, i));
	}
}

void MergeVector(Vector* src, Vector* dst) {
	for(int i=0; i<src->length; i++) {
		VectorItem e = AtVector(src, i);
		PushVector(dst, e);
	}
}
#undef SLOT_SIZE