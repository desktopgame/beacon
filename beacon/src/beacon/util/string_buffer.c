#include "string_buffer.h"
#include "mem.h"
#include <assert.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif
//proto
string_buffer* string_buffer_malloc(const char* filename, int lineno) {
	string_buffer* ret = mem_malloc(sizeof(string_buffer), filename, lineno);
	ret->length = 0;
	ret->capacity = 16;
	ret->text = (char*)mem_malloc(sizeof(char) * 16, filename, lineno);
	memset(ret->text, '\0', 16);
	return ret;
}

void string_buffer_append(string_buffer * self, char c) {
	if (self->length >= self->capacity) {
		string_buffer_reserve(self);
	}
	self->text[self->length] = c;
	self->length++;
}

void string_buffer_appendf(string_buffer * self, const char * fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	string_buffer_vappendf(self, fmt, ap);
	va_end(ap);
}

void string_buffer_vappendf(string_buffer * self, const char * fmt, va_list ap) {
#define BUFF_LEN (256)
	char block[BUFF_LEN];
	memset(block, '\0', BUFF_LEN);
	int res = vsprintf(block, fmt, ap);
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

string_buffer* string_buffer_indent(string_buffer* self, int lineIndex, int len) {
	string_buffer* buf = string_buffer_new();
	int linec = 0;
	int pos = 0;
	for(int i=0; i<self->length; i++) {
		char c = self->text[i];
		if(pos == 0 &&
			((linec >= lineIndex && linec < (lineIndex + len)) ||
			(lineIndex == -1 && len == -1))
		) {
			string_buffer_appends(buf, "    ");
		}
		if(c == '\n') {
			linec++;
			pos = 0;
			string_buffer_append(buf, '\n');
		} else {
			string_buffer_append(buf, c);
			pos++;
		}
	}
	return buf;
}

void string_buffer_delete(string_buffer * self) {
	MEM_FREE(self->text);
	MEM_FREE(self);
}