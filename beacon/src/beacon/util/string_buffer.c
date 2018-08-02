#include "string_buffer.h"
#include "mem.h"
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

//proto
static void string_buffer_fill_zero(string_buffer* self, int offs, int len);

string_buffer* string_buffer_malloc(const char* filename, int lineno) {
	string_buffer* ret = (string_buffer*)mem_malloc(sizeof(string_buffer), filename, lineno);
	ret->length = 0;
	ret->capacity = 16;
	ret->text = (char*)mem_malloc(sizeof(char) * 16, filename, lineno);
	string_buffer_fill_zero(ret, 0, 16);
	return ret;
}

void string_buffer_append(string_buffer * self, char c) {
	if (self->length >= self->capacity) {
		string_buffer_reserve(self);
	}
	self->text[self->length] = c;
	self->length++;
}

void string_buffer_appendf(string_buffer * self, const char * message, ...) {
	va_list ap;
	va_start(ap, message);

	string_buffer_vappendf(self, message, ap);
	va_end(ap);
}

void string_buffer_vappendf(string_buffer * self, const char * message, va_list ap) {
#define BUFF_LEN (256)
	char block[BUFF_LEN];
	memset(block, '\0', BUFF_LEN);
	#if defined(_MSC_VER)
	int res = vsprintf_s(block, BUFF_LEN, message, ap);
	#else
	int res = vsprintf(block, message, ap);
	#endif
	assert(res != -1);
	int len = strlen(block);
	for (int i = 0; i < len; i++) {
		char c = block[i];
		if (c == '\0') { break; }
		string_buffer_append(self, c);
	}

#undef BUFF_LEN
}

void string_buffer_appends(string_buffer * self, const char * s) {
	for (int i = 0; ; i++) {
		char c = s[i];
		if (c == '\0') break;
		string_buffer_append(self, c);
	}
}

char* string_buffer_release(string_buffer* self) {
	string_buffer_shrink(self);
	char* ret = self->text;
	self->text = NULL;
	MEM_FREE(self);
	return ret;
}

void string_buffer_reserve(string_buffer* self) {
	int newSize = self->capacity + (self->capacity / 2);
	char* temp = (char*)MEM_REALLOC(self->text, newSize);
	assert(temp != NULL);
	//新しく確保された部分を 0埋め
	self->text = temp;
	self->capacity = newSize;
}

void string_buffer_shrink(string_buffer * self) {
	if (self->length == 0) {
		return;
	}
	char* temp = (char*)MEM_REALLOC(self->text, self->length + 1);
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