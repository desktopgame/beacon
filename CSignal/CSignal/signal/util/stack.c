#include "stack.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/mem.h"

stack * stack_new() {
	stack* st = (stack*)MEM_MALLOC(sizeof(stack));
	st->item = NULL;
	st->prev = NULL;
	st->next = NULL;
	return st;
}

void stack_push(stack * self, stack_item item) {
	assert(self != NULL);
	assert(item != NULL);
	if (self->item == NULL) {
		self->item = item;
		return;
	}
	if (self->next == NULL) {
		stack* nextElement = stack_new();
		self->next = nextElement;
		nextElement->prev = self;
		nextElement->item = item;
	} else {
		stack_push(self->next, item);
	}
}

stack_item stack_top(stack * self) {
	assert(self != NULL);
	if (self->next == NULL) {
		return self->item;
	} else {
		return stack_top(self->next);
	}
}

stack_item stack_pop(stack * self) {
	assert(self != NULL);
	if (self->next == NULL) {
		if (self->prev == NULL) {
			stack_item ret = self->item;
			self->item = NULL;
			return ret;
		} else {
			stack* prevElement = self->prev;
			prevElement->next = NULL;
			self->prev = NULL;
			stack_item ret = self->item;
			MEM_FREE(self);
			return ret;
		}
	} else {
		return stack_pop(self->next);
	}
}

bool stack_empty(stack * self) {
	assert(self != NULL);
	return (self->item == NULL);
}

void stack_delete(stack * self, stack_element_deleter deleter) {
	assert(self != NULL);
	stack* pointee = self;
	while (1) {
		stack* next = pointee->next;
		pointee->next = NULL;
		if (next) {
			next->prev = NULL;
		}
		stack_item item = pointee->item;
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

void stack_deleter_free(stack_item item) {
	MEM_FREE(item);
}

void stack_deleter_null(stack_item item) {
}
