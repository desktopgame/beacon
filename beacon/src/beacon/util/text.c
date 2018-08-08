#include "text.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "mem.h"
#include "string_buffer.h"
#include "io.h"

//proto
static char* text_strclone(const char* source);
static char* text_readlineImpl(FILE* fp);
static FILE* text_fp = NULL;
static FILE* fake_stdout = NULL;
static FILE* real_stdout = NULL;

void text_putline() {
#if defined(_WIN32)
	text_printf("\n");
#else
	text_printf("\n");
#endif // defined(_WIN32)
}

void text_putb(bool b) {
	text_printf("%s", (b ? "true" : "false"));
}

void text_printr(char ch, int count) {
	for(int i=0; i<count; i++) {
		text_printf("%c", ch);
	}
}

int text_fprintf(FILE* fp, const char* message, ...) {
	va_list ap;
	va_start(ap, message);
	int res = text_vfprintf(fp, message, ap);
	va_end(ap);
	return res;
}

int text_vfprintf(FILE* fp, const char* message, va_list ap) {
	int res = vfprintf(fp, message, ap);
	return res;
}

int text_printf(const char * message, ...) {
	va_list ap;

	va_start(ap, message);
	int res = text_vprintf(message, ap);
	va_end(ap);
	return res;
}

int text_vprintf(const char * message, va_list ap) {
	//text_printfdbg(message, ap);
	int res = vprintf(message, ap);
	return res;
}

int text_sprintf(char * block, size_t blockSize, char * message, ...) {
	va_list ap;
	va_start(ap, message);
	int res = text_vsprintf(block, blockSize, message, ap);
	va_end(ap);
	return 0;
}

int text_vsprintf(char * block, size_t blockSize, char * message, va_list ap) {
	int res = 0;
#if defined(_MSC_VER)
	res = vsprintf_s(block, blockSize, message, ap);
#else
	res = vsprintf(block, message, ap);
#endif
	return res;
}

void text_printfln(const char * message, ...) {
	va_list ap;
	va_start(ap, message);
	text_vprintf(message, ap);
#if defined(_MSC_VER)
	text_printf("\n");
#else
	text_printf("\r\n");
#endif
	va_end(ap);
}

void text_putindent(int depth) {
	for(int i=0; i<depth; i++) {
		text_printf("    ");
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

bool text_white(const char * str) {
	assert(str != NULL);
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		char e = str[i];
		if (e != ' ' &&
			e != '\n' && 
			!isspace(e)) {
			return false;
		}
	}
	return true;
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
	#if defined(_MSC_VER)
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
	#else
	string_buffer* buff = string_buffer_new();
	string_buffer_appends(buff, a);
	string_buffer_appends(buff, b);
	char* ret = string_buffer_release(buff);
	return ret;
	#endif
}

char * text_lineat(const char * src, int lineno) {
	//text_printf("%s", src);
	//return NULL;
	if(src == NULL) {
		return NULL;
	}
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

bool text_contains(const char* source, const char* text) {
	int pos = 0;
	int slen = strlen(source);
	int tlen = strlen(text);
	for(int i=0; i<slen; i++) {
		char ch = source[i];
		int diff = tlen - pos;
		if(i + diff > slen) {
			break;
		}
		if(ch == text[pos]) {
			pos++;
			if(pos == tlen) {
				return true;
			}
		} else {
			pos = 0;
		}
	}
	return false;
}

char* text_readline() {
	return text_readlineImpl(stdin);
}

char* text_freadline(FILE* fp) {
	return text_readlineImpl(fp);
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

static char* text_readlineImpl(FILE* fp) {
	string_buffer* sb = string_buffer_new();
	while(1) {
		char ch = getc(fp);
		if(ch == '\0' || ch == '\n' || feof(fp)) {
			break;
		}
		string_buffer_append(sb, ch);
	}
	return string_buffer_release(sb);
}