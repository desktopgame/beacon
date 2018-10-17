#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/mem.h"

Stack* NewStack() {
	Stack* ret = (Stack*)MEM_MALLOC(sizeof(Stack));
	ret->Item = NULL;
	ret->Prev = NULL;
	ret->Next = NULL;
	return ret;
}

void PushStack(Stack* self, StackItem item) {
	assert(self != NULL);
	assert(item != NULL);
	if (self->Item == NULL) {
		self->Item = item;
		return;
	}
	if (self->Next == NULL) {
		Stack* next_elem = NewStack();
		self->Next = next_elem;
		next_elem->Prev = self;
		next_elem->Item = item;
	} else {
		PushStack(self->Next, item);
	}
}

StackItem TopStack(Stack* self) {
	assert(self != NULL);
	if (self->Next == NULL) {
		return self->Item;
	} else {
		return TopStack(self->Next);
	}
}

StackItem PopStack(Stack* self) {
	assert(self != NULL);
	if (self->Next == NULL) {
		if (self->Prev == NULL) {
			StackItem ret = self->Item;
			self->Item = NULL;
			return ret;
		} else {
			Stack* prev_elem = self->Prev;
			prev_elem->Next = NULL;
			self->Prev = NULL;
			StackItem ret = self->Item;
			MEM_FREE(self);
			return ret;
		}
	} else {
		return PopStack(self->Next);
	}
}

bool IsEmptyStack(Stack * self) {
	assert(self != NULL);
	return (self->Item == NULL);
}

void DeleteStack(Stack* self, StackElementDeleter deleter) {
	assert(self != NULL);
	Stack* pointee = self;
	while (1) {
		Stack* next = pointee->Next;
		pointee->Next = NULL;
		if (next) {
			next->Prev = NULL;
		}
		StackItem item = pointee->Item;
		pointee->Item = NULL;
		if (item) {
			deleter(item);
		}
		MEM_FREE(pointee);
		pointee = next;
		if (!next) {
			break;
		}
	}
}

void StackDeleterByFree(StackItem item) {
	MEM_FREE(item);
}

void StackDeleterOfNull(StackItem item) {
}
