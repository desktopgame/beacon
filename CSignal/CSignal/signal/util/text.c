#include "text.h"
#include "logger.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

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
