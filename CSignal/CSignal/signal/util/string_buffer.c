#include "string_buffer.h"
#include "mem.h"
#include <assert.h>
#include <stdio.h>

//proto
static void string_buffer_fill_zero(string_buffer* self, int offs, int len);

string_buffer * string_buffer_new() {
	string_buffer* ret = (string_buffer*)MEM_MALLOC(sizeof(string_buffer));
	ret->length = 0;
	ret->capacity = 16;
	ret->text = (char*)MEM_MALLOC(sizeof(char) * 16);
	string_buffer_fill_zero(ret, 0, 16);
	return ret;
}

void string_buffer_append(string_buffer * self, char_t c) {
	//printf("%c", c);
	//printf("[%c]\n", c);
	if (self->length >= self->capacity) {
		int newSize = self->capacity + (self->capacity / 2);
		char_t* temp = (char*)MEM_REALLOC(self->text, newSize);
		assert(temp != NULL);
		//新しく確保された部分を 0埋め
		self->text = temp;
		self->capacity = newSize;
		//string_buffer_fill_zero(self, self->length, newSize);
	}
	self->text[self->length] = c;
	self->length++;
}

void string_buffer_shrink(string_buffer * self) {
	if (self->length == self->capacity) {
		return;
	}
	if (self->length == 0) {
		return;
	}
	char_t* temp = (char*)MEM_REALLOC(self->text, self->length);
	assert(temp != NULL);
	temp[self->length] = '\0';
	self->text = temp;
	self->capacity = self->length;
}

void string_buffer_delete(string_buffer * self) {
	MEM_FREE(self->text);
	MEM_FREE(self);
}

//private
static void string_buffer_fill_zero(string_buffer* self, int offs, int len) {
	for (int i = offs; i < offs + len; i++) {
		self->text[i] = '\0';
	}
}