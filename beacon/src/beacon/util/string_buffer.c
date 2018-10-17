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
StringBuffer* MallocBuffer(const char* filename, int lineno) {
	StringBuffer* ret = mem_malloc(sizeof(StringBuffer), filename, lineno);
	ret->Length = 0;
	ret->Capacity = 16;
	ret->Text = (char*)mem_malloc(sizeof(char) * 16, filename, lineno);
	memset(ret->Text, '\0', 16);
	return ret;
}

void AppendBuffer(StringBuffer * self, char c) {
	if (self->Length >= self->Capacity) {
		ReserveBuffer(self);
	}
	self->Text[self->Length] = c;
	self->Length++;
}

void AppendfBuffer(StringBuffer * self, const char * fmt, ...) {
	va_list ap;
	va_start(ap, fmt);

	VappendfBuffer(self, fmt, ap);
	va_end(ap);
}

void VappendfBuffer(StringBuffer * self, const char * fmt, va_list ap) {
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

void AppendsBuffer(StringBuffer * self, const char * s) {
	for (int i = 0; ; i++) {
		char c = s[i];
		if (c == '\0') break;
		AppendBuffer(self, c);
	}
}

char* ReleaseBuffer(StringBuffer* self) {
	ShrinkBuffer(self);
	char* ret = self->Text;
	self->Text = NULL;
	MEM_FREE(self);
	return ret;
}

void ReserveBuffer(StringBuffer* self) {
	int newSize = self->Capacity + (self->Capacity / 2);
	char* temp = (char*)MEM_REALLOC(self->Text, newSize);
	assert(temp != NULL);
	//新しく確保された部分を 0埋め
	self->Text = temp;
	self->Capacity = newSize;
}

void ShrinkBuffer(StringBuffer * self) {
	if (self->Length == 0) {
		return;
	}
	char* temp = (char*)MEM_REALLOC(self->Text, self->Length + 1);
	assert(temp != NULL);
	temp[self->Length] = '\0';
	self->Text = temp;
	self->Capacity = self->Length;
}

StringBuffer* IndentBuffer(StringBuffer* self, int lineIndex, int len) {
	StringBuffer* buf = NewBuffer();
	int linec = 0;
	int pos = 0;
	for(int i=0; i<self->Length; i++) {
		char c = self->Text[i];
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

void DeleteBuffer(StringBuffer * self) {
	MEM_FREE(self->Text);
	MEM_FREE(self);
}