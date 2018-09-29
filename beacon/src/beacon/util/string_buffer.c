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
string_buffer* MallocBuffer(const char* filename, int lineno) {
	string_buffer* ret = mem_malloc(sizeof(string_buffer), filename, lineno);
	ret->length = 0;
	ret->capacity = 16;
	ret->text = (char*)mem_malloc(sizeof(char) * 16, filename, lineno);
	memset(ret->text, '\0', 16);
	return ret;
}

void AppendBuffer(string_buffer * self, char c) {
	if (self->length >= self->capacity) {
		ReserveBuffer(self);
	}
	self->text[self->length] = c;
	self->length++;
}

void AppendfBuffer(string_buffer * self, const char * fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	VappendfBuffer(self, fmt, ap);
	va_end(ap);
}

void VappendfBuffer(string_buffer * self, const char * fmt, va_list ap) {
#define BUFF_LEN (256)
	char block[BUFF_LEN];
	memset(block, '\0', BUFF_LEN);
	int res = vsprintf(block, fmt, ap);
	assert(res != -1);
	int len = strlen(block);
	for (int i = 0; i < len; i++) {
		char c = block[i];
		if (c == '\0') { break; }
		AppendBuffer(self, c);
	}

#undef BUFF_LEN
}

void AppendsBuffer(string_buffer * self, const char * s) {
	for (int i = 0; ; i++) {
		char c = s[i];
		if (c == '\0') break;
		AppendBuffer(self, c);
	}
}

char* ReleaseBuffer(string_buffer* self) {
	ShrinkBuffer(self);
	char* ret = self->text;
	self->text = NULL;
	MEM_FREE(self);
	return ret;
}

void ReserveBuffer(string_buffer* self) {
	int newSize = self->capacity + (self->capacity / 2);
	char* temp = (char*)MEM_REALLOC(self->text, newSize);
	assert(temp != NULL);
	//新しく確保された部分を 0埋め
	self->text = temp;
	self->capacity = newSize;
}

void ShrinkBuffer(string_buffer * self) {
	if (self->length == 0) {
		return;
	}
	char* temp = (char*)MEM_REALLOC(self->text, self->length + 1);
	assert(temp != NULL);
	temp[self->length] = '\0';
	self->text = temp;
	self->capacity = self->length;
}

string_buffer* IndentBuffer(string_buffer* self, int lineIndex, int len) {
	string_buffer* buf = NewBuffer();
	int linec = 0;
	int pos = 0;
	for(int i=0; i<self->length; i++) {
		char c = self->text[i];
		if(pos == 0 &&
			((linec >= lineIndex && linec < (lineIndex + len)) ||
			(lineIndex == -1 && len == -1))
		) {
			AppendsBuffer(buf, "    ");
		}
		if(c == '\n') {
			linec++;
			pos = 0;
			AppendBuffer(buf, '\n');
		} else {
			AppendBuffer(buf, c);
			pos++;
		}
	}
	return buf;
}

void DeleteBuffer(string_buffer * self) {
	MEM_FREE(self->text);
	MEM_FREE(self);
}