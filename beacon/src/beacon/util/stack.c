#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/mem.h"

Stack* NewStack() {
	Stack* ret = (Stack*)MEM_MALLOC(sizeof(Stack));
	ret->item = NULL;
	ret->prev = NULL;
	ret->next = NULL;
	return ret;
}

void PushStack(Stack* self, StackItem item) {
	assert(self != NULL);
	assert(item != NULL);
	if (self->item == NULL) {
		self->item = item;
		return;
	}
	if (self->next == NULL) {
		Stack* next_elem = NewStack();
		self->next = next_elem;
		next_elem->prev = self;
		next_elem->item = item;
	} else {
		PushStack(self->next, item);
	}
}

StackItem TopStack(Stack* self) {
	assert(self != NULL);
	if (self->next == NULL) {
		return self->item;
	} else {
		return TopStack(self->next);
	}
}

StackItem PopStack(Stack* self) {
	assert(self != NULL);
	if (self->next == NULL) {
		if (self->prev == NULL) {
			StackItem ret = self->item;
			self->item = NULL;
			return ret;
		} else {
			Stack* prev_elem = self->prev;
			prev_elem->next = NULL;
			self->prev = NULL;
			StackItem ret = self->item;
			MEM_FREE(self);
			return ret;
		}
	} else {
		return PopStack(self->next);
	}
}

bool IsEmptyStack(Stack * self) {
	assert(self != NULL);
	return (self->item == NULL);
}

void DeleteStack(Stack* self, StackElementDeleter deleter) {
	assert(self != NULL);
	Stack* pointee = self;
	while (1) {
		Stack* next = pointee->next;
		pointee->next = NULL;
		if (next) {
			next->prev = NULL;
		}
		StackItem item = pointee->item;
		pointee->item = NULL;
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
