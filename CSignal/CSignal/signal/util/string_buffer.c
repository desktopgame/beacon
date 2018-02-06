#include "string_buffer.h"
#include "mem.h"
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

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
	//text_printf("%c", c);
	//text_printf("[%c]\n", c);
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

void string_buffer_appendf(string_buffer * self, const char * message, ...) {
	va_list ap;
	va_start(ap, message);

#define BUFF_LEN (256)
	char block[BUFF_LEN];
	memset(block, '\0', BUFF_LEN);
	int res = vsprintf_s(block, BUFF_LEN, message, ap);
	assert(res != -1);
	int len = strlen(block);
	for (int i = 0; i < len; i++) {
		char c = block[i];
		if (c == '\0') { break; }
		string_buffer_append(self, c);
	}

	va_end(ap);
#undef BUFF_LEN
}

void string_buffer_appends(string_buffer * self, const char * s) {
	for (int i = 0; ; i++) {
		char c = s[i];
		if (c == '\0') break;
		string_buffer_append(self, c);
	}
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