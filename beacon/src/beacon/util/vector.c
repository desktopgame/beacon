#include "vector.h"
#include <assert.h>
#include "mem.h"

#define SLOT_SIZE sizeof(void*)

bc_Vector* bc_MallocVector(const char* filename, int lineno) {
	bc_Vector* ret = (bc_Vector*)bc_MXMalloc(sizeof(bc_Vector), filename, lineno);
	ret->Length = 0;
	ret->Capacity = 16;
	ret->Memory = (bc_VectorItem*)bc_MXMalloc(SLOT_SIZE * 16, filename, lineno);
	return ret;
}

void bc_PushVector(bc_Vector * self, bc_VectorItem item) {
	assert(self != NULL);
	if (self->Length >= self->Capacity) {
		bc_ReserveVector(self);
	}
	self->Memory[self->Length] = item;
	self->Length++;
}

bc_Vector* bc_AppendVector(bc_Vector* self, bc_VectorItem item) {
	if(self == NULL) {
		self = bc_NewVector();
	}
	bc_PushVector(self, item);
	return self;
}

bc_VectorItem bc_TopVector(bc_Vector * self) {
	assert(self != NULL);
	assert(self->Length > 0);
	return *(self->Memory + (self->Length - 1));
}

bc_VectorItem bc_PopVector(bc_Vector * self) {
	assert(self != NULL);
	assert(self->Length > 0);
	bc_VectorItem ret = self->Memory[self->Length - 1];
	//二重に開放しないように
	self->Memory[self->Length - 1] = NULL;
	self->Length--;
	return ret;
}

void bc_InsertVector(bc_Vector * self, int index, bc_VectorItem item) {
	assert(index >= 0 && index < (self->Length + 1));
	if (self->Capacity < (self->Length + 1)) {
		bc_ReserveVector(self);
	}
	bc_VectorItem t = self->Memory[index];
	for (int i = index; i < self->Length; i++) {
		bc_VectorItem b = self->Memory[i + 1];
		self->Memory[i + 1] = t;
		t = b;
	}
	self->Memory[index] = item;
	self->Length++;
}

bc_VectorItem bc_RemoveVector(bc_Vector * self, int index) {
	assert(index >= 0 && index < self->Length);
	bc_VectorItem ret = self->Memory[index];
	for (int i = index + 1; i < self->Length; i++) {
		self->Memory[i - 1] = self->Memory[i];
	}
	self->Length--;
	return ret;
}

void bc_PackVector(bc_Vector* self) {
	assert(self != NULL);
	self->Memory = MEM_REALLOC(self->Memory, SLOT_SIZE * self->Length);
	self->Capacity = self->Length;
}

int bc_ReserveVector(bc_Vector * self) {
	assert(self->Capacity > 0);
	int newCapacitySize = self->Capacity + (self->Capacity / 2);
	bc_VectorItem* temp = MEM_REALLOC(self->Memory, SLOT_SIZE * newCapacitySize);
	assert(temp != NULL);
	self->Memory = temp;
	self->Capacity = newCapacitySize;
	return newCapacitySize;
}

void bc_AssignVector(bc_Vector * self, int index, bc_VectorItem item) {
	assert(index >= 0);
	//伸ばす必要がない
	if (index < self->Length) {
		self->Memory[index] = item;
	} else {
		while (self->Length <= index) {
			bc_PushVector(self, NULL);
		}
		bc_AssignVector(self, index, item);
	}
}

bc_VectorItem bc_AtVector(bc_Vector * self, int index) {
	assert(index >= 0 && index < self->Length);
	return self->Memory[index];
}

bc_Vector* bc_SubVector(bc_Vector* self, int offset, int len) {
	assert(offset >= 0);
	if(len == 0) {
		return bc_NewVector();
	}
	bc_Vector* v = bc_NewVector();
	for(int i=offset; i<offset+len; i++) {
		bc_PushVector(v, bc_AtVector(self, i));
	}
	return v;
}

bool bc_IsEmptyVector(bc_Vector * self) {
	return self->Length == 0;
}

int bc_FindVector(bc_Vector * self, bc_VectorItem item) {
	int pos = -1;
	for (int i = 0; i < self->Length; i++) {
		bc_VectorItem e = bc_AtVector(self, i);
		if (e == item) {
			pos = i;
			break;
		}
	}
	return pos;
}

bool bc_IsContainsVector(bc_Vector * self, bc_VectorItem item) {
	return bc_FindVector(self, item);
}

void bc_ClearVector(bc_Vector * self) {
	while (self->Length > 0) {
		bc_PopVector(self);
	}
}

void bc_DeleteVector(bc_Vector * self, bc_VectorElementDeleter deleter) {
	if (self == NULL) {
		return;
	}
	//vector_pack(self);
	for (int i = 0; i < self->Length; i++) {
		bc_VectorItem e = self->Memory[i];
		self->Memory[i] = NULL;
		deleter(e);
	}
	MEM_FREE(self->Memory);
	self->Memory = NULL;
	MEM_FREE(self);
}

void bc_VectorDeleterByFree(bc_VectorItem item) {
	MEM_FREE(item);
}

void bc_VectorDeleterOfNull(bc_VectorItem item) {
}

bc_Vector* bc_CloneVector(bc_Vector* source) {
	bc_Vector* ret = bc_NewVector();
	for(int i=0; i<source->Length; i++) {
		bc_PushVector(ret, bc_AtVector(source, i));
	}
	return ret;
}

void bc_CopyVector(bc_Vector* src, bc_Vector* dst) {
	assert(dst->Length == 0);
	for(int i=0; i<src->Length; i++) {
		bc_PushVector(dst, bc_AtVector(src, i));
	}
}

void bc_EachVector(bc_Vector* self, bc_VectorAction a) {
	for(int i=0; i<self->Length; i++) {
		a(bc_AtVector(self, i));
	}
}

void bc_MergeVector(bc_Vector* src, bc_Vector* dst) {
	for(int i=0; i<src->Length; i++) {
		bc_VectorItem e = bc_AtVector(src, i);
		bc_PushVector(dst, e);
	}
}
#undef SLOT_SIZE