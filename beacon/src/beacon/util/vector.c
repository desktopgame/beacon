#include "vector.h"
#include <assert.h>
#include "mem.h"

#define SLOT_SIZE sizeof(void*)

Vector* MallocVector(const char* filename, int lineno) {
	Vector* ret = (Vector*)bc_MXMalloc(sizeof(Vector), filename, lineno);
	ret->Length = 0;
	ret->Capacity = 16;
	ret->Memory = (VectorItem*)bc_MXMalloc(SLOT_SIZE * 16, filename, lineno);
	return ret;
}

void PushVector(Vector * self, VectorItem item) {
	assert(self != NULL);
	if (self->Length >= self->Capacity) {
		ReserveVector(self);
	}
	self->Memory[self->Length] = item;
	self->Length++;
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
	assert(self->Length > 0);
	return *(self->Memory + (self->Length - 1));
}

VectorItem PopVector(Vector * self) {
	assert(self != NULL);
	assert(self->Length > 0);
	VectorItem ret = self->Memory[self->Length - 1];
	//二重に開放しないように
	self->Memory[self->Length - 1] = NULL;
	self->Length--;
	return ret;
}

void InsertVector(Vector * self, int index, VectorItem item) {
	assert(index >= 0 && index < (self->Length + 1));
	if (self->Capacity < (self->Length + 1)) {
		ReserveVector(self);
	}
	VectorItem t = self->Memory[index];
	for (int i = index; i < self->Length; i++) {
		VectorItem b = self->Memory[i + 1];
		self->Memory[i + 1] = t;
		t = b;
	}
	self->Memory[index] = item;
	self->Length++;
}

VectorItem RemoveVector(Vector * self, int index) {
	assert(index >= 0 && index < self->Length);
	VectorItem ret = self->Memory[index];
	for (int i = index + 1; i < self->Length; i++) {
		self->Memory[i - 1] = self->Memory[i];
	}
	self->Length--;
	return ret;
}

void PackVector(Vector* self) {
	assert(self != NULL);
	self->Memory = MEM_REALLOC(self->Memory, SLOT_SIZE * self->Length);
	self->Capacity = self->Length;
}

int ReserveVector(Vector * self) {
	assert(self->Capacity > 0);
	int newCapacitySize = self->Capacity + (self->Capacity / 2);
	VectorItem* temp = MEM_REALLOC(self->Memory, SLOT_SIZE * newCapacitySize);
	assert(temp != NULL);
	self->Memory = temp;
	self->Capacity = newCapacitySize;
	return newCapacitySize;
}

void AssignVector(Vector * self, int index, VectorItem item) {
	assert(index >= 0);
	//伸ばす必要がない
	if (index < self->Length) {
		self->Memory[index] = item;
	} else {
		while (self->Length <= index) {
			PushVector(self, NULL);
		}
		AssignVector(self, index, item);
	}
}

VectorItem AtVector(Vector * self, int index) {
	assert(index >= 0 && index < self->Length);
	return self->Memory[index];
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
	return self->Length == 0;
}

int FindVector(Vector * self, VectorItem item) {
	int pos = -1;
	for (int i = 0; i < self->Length; i++) {
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
	while (self->Length > 0) {
		PopVector(self);
	}
}

void DeleteVector(Vector * self, VectorElementDeleter deleter) {
	if (self == NULL) {
		return;
	}
	//vector_pack(self);
	for (int i = 0; i < self->Length; i++) {
		VectorItem e = self->Memory[i];
		self->Memory[i] = NULL;
		deleter(e);
	}
	MEM_FREE(self->Memory);
	self->Memory = NULL;
	MEM_FREE(self);
}

void VectorDeleterByFree(VectorItem item) {
	MEM_FREE(item);
}

void VectorDeleterOfNull(VectorItem item) {
}

Vector* CloneVector(Vector* source) {
	Vector* ret = NewVector();
	for(int i=0; i<source->Length; i++) {
		PushVector(ret, AtVector(source, i));
	}
	return ret;
}

void CopyVector(Vector* src, Vector* dst) {
	assert(dst->Length == 0);
	for(int i=0; i<src->Length; i++) {
		PushVector(dst, AtVector(src, i));
	}
}

void EachVector(Vector* self, VectorAction a) {
	for(int i=0; i<self->Length; i++) {
		a(AtVector(self, i));
	}
}

void MergeVector(Vector* src, Vector* dst) {
	for(int i=0; i<src->Length; i++) {
		VectorItem e = AtVector(src, i);
		PushVector(dst, e);
	}
}
#undef SLOT_SIZE