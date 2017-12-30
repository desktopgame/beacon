#include "text.h"
#include "logger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

//proto
static char* text_strclone(const char* source);

void text_putline() {
#if defined(_WIN32)
	printf("\n");
#else
	printf("\n");
#endif // defined(_WIN32)
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

char* text_sum(vector * v, char * join) {
	if (v == NULL || v->length == 0) {
		return NULL;
	}
	//FIXME:Ç‡Ç§ÇøÇÂÇ¡Ç∆çÇë¨Ç…èoóàÇÈ
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