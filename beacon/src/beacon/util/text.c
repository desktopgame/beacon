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
static char* read_line_impl(FILE* fp);
static FILE* text_fp = NULL;
static FILE* fake_stdout = NULL;
static FILE* real_stdout = NULL;

char * Strdup(const char * source) {
	if (source == NULL) {
		return NULL;
	}
	//\0を含める
	return bc_Bind(source, (strlen(source) + 1) * sizeof(char));
}

bool IsBlankText(const char * str) {
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

char * ConcatString(const char * a, const char * b) {
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
	Buffer* buff = NewBuffer();
	AppendsBuffer(buff, a);
	AppendsBuffer(buff, b);
	char* ret = ReleaseBuffer(buff);
	return ret;
	#endif
}

char * GetLineAt(const char * src, int lineno) {
	//printf("%s", src);
	//return NULL;
	if(src == NULL) {
		return NULL;
	}
	int len = strlen(src);
	int curLine = 0;
	Buffer* buf = NewBuffer();
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
	char* ret = buf->Text;
	MEM_FREE(buf);
	return ret;
}

char* JoinString(Vector * v, char * join) {
	if (v == NULL || v->Length == 0) {
		return NULL;
	}
	//FIXME:もうちょっと無駄をなくせるはず
	char* head = Strdup((char*)AtVector(v, 0));
	int ptr = strlen(head);
	for (int i = 1; i < v->Length; i++) {
		char* e = (char*)AtVector(v, i);
		if (i <= (v->Length - 1) && 
			join != NULL) {
			char* conn = ConcatString(head, join);
			MEM_FREE(head);
			head = conn;
		}
		char* ret = ConcatString(head, e);
		MEM_FREE(head);
		head = ret;
	}
	return head;
}

bool IsIncluded(const char* source, const char* text) {
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

char* ReadLine() {
	return read_line_impl(stdin);
}

char* FreadLine(FILE* fp) {
	return read_line_impl(fp);
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

static char* read_line_impl(FILE* fp) {
	Buffer* sb = NewBuffer();
	while(1) {
		char ch = getc(fp);
		if(ch == '\0' || ch == '\n' || feof(fp)) {
			break;
		}
		AppendBuffer(sb, ch);
	}
	return ReleaseBuffer(sb);
}