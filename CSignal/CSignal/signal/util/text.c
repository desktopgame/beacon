#include "text.h"
#include "logger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"
#include "string_buffer.h"

//proto
static char* text_strclone(const char* source);

void text_putline() {
#if defined(_WIN32)
	printf("\n");
#else
	printf("\n");
#endif // defined(_WIN32)
}

void text_putb(bool b) {
	printf("%s", (b ? "true" : "false"));
}

void text_printfln(const char * message, ...) {
	va_list ap;
	va_start(ap, message);
	printf(message, ap);
#if defined(_MSC_VER)
	printf("\n");
#else
	printf("\r\n");
#endif
	va_end(ap);
}

void text_putindent(int depth) {
	for(int i=0; i<depth; i++) {
		printf("    ");
	}
}

char * text_strdup(const char * source) {
	if (source == NULL) {
		return NULL;
	}
	char* ret = NULL;
#if defined(_MSC_VER)
	ret = _strdup(source);
#else
	ret = strdup(source);
#endif
	mem_inc();
	assert(ret != NULL) ;
	return ret;
}

char * text_gets() {
	string_buffer* sb = string_buffer_new();
	while (true) {
		char c = getchar();
		if (c == '\n') {
			string_buffer_shrink(sb);
			break;
		} else {
			string_buffer_append(sb, c);
		}
	}
	char* ret = sb->text;
	MEM_FREE(sb);
	return ret;
}

SG_errno_t text_strncpy(char * outChar, size_t index, const char * source, size_t dataSize) {
#if defined(_MSC_VER)
	return strncpy_s(outChar, index, source, dataSize);
#else
	strncpy(outChar, source + index, dataSize);
#endif
	return NULL;
}

char * text_concat(const char * a, const char * b) {
	int alen = strlen(a);
	int blen = strlen(b);
	char* block = (char*)MEM_MALLOC((sizeof(char) * (alen + blen)) + 1);
	for (int i = 0; i < alen; i++) {
		block[i] = a[i];
	}
	for (int i = 0; i < blen; i++) {
		block[alen + i] = b[i];
	}
	block[alen + blen] = '\0';
	return block;
}

char * text_lineat(const char * src, int lineno) {
	printf("%s", src);
	//return NULL;
	int len = strlen(src);
	int curLine = 0;
	string_buffer* buf = string_buffer_new();
	char* PTR = NULL;
	for (int i = 0; i < len; i++) {
		char c = src[i];
		if (c == '\0') { break; }
		if (c == '\n') {
			if (lineno == curLine) {
				break;
			}
			curLine++;
		} else {
			if (lineno == 0 || lineno == curLine) {
				string_buffer_append(buf, c);
			}
		}
	}
	string_buffer_shrink(buf);
	char* ret = buf->text;
	MEM_FREE(buf);
	return ret;
}

char* text_sum(vector * v, char * join) {
	if (v == NULL || v->length == 0) {
		return NULL;
	}
	//FIXME:もうちょっと無駄をなくせるはず
	char* head = text_strdup((char*)vector_at(v, 0));
	int ptr = strlen(head);
	for (int i = 1; i < v->length; i++) {
		char* e = (char*)vector_at(v, i);
		if (i <= (v->length - 1) && 
			join != NULL) {
			char* conn = text_concat(head, join);
			MEM_FREE(head);
			head = conn;
		}
		char* ret = text_concat(head, e);
		MEM_FREE(head);
		head = ret;
	}
	return head;
}

//private
static char* text_strclone(const char* source) {
	int len = strlen(source);
	char* block = (char*)malloc(len + 1);
	for (int i = 0; i < len; i++) {
		block[i] = source[i];
	}
	block[len] = '\0';
	return block;
}