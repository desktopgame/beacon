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
	string_buffer* sb = NewBuffer();
	while (true) {
		char c = getchar();
		if (c == '\n') {
			ShrinkBuffer(sb);
			break;
		} else {
			AppendBuffer(sb, c);
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
	string_buffer* buff = NewBuffer();
	AppendsBuffer(buff, a);
	AppendsBuffer(buff, b);
	char* ret = ReleaseBuffer(buff);
	return ret;
	#endif
}

char * text_lineat(const char * src, int lineno) {
	//printf("%s", src);
	//return NULL;
	if(src == NULL) {
		return NULL;
	}
	int len = strlen(src);
	int curLine = 0;
	string_buffer* buf = NewBuffer();
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
				AppendBuffer(buf, c);
			}
		}
	}
	ShrinkBuffer(buf);
	char* ret = buf->text;
	MEM_FREE(buf);
	return ret;
}

char* text_sum(Vector * v, char * join) {
	if (v == NULL || v->length == 0) {
		return NULL;
	}
	//FIXME:もうちょっと無駄をなくせるはず
	char* head = text_strdup((char*)AtVector(v, 0));
	int ptr = strlen(head);
	for (int i = 1; i < v->length; i++) {
		char* e = (char*)AtVector(v, i);
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
	string_buffer* sb = NewBuffer();
	while(1) {
		char ch = getc(fp);
		if(ch == '\0' || ch == '\n' || feof(fp)) {
			break;
		}
		AppendBuffer(sb, ch);
	}
	return ReleaseBuffer(sb);
}