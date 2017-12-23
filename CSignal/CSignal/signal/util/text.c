#include "text.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
#if defined(_MSC_VER)
	return _strdup(source);
#else
	return strdup(source);
#endif
}

char * text_concat(const char * a, const char * b) {
	int alen = strlen(a);
	int blen = strlen(b);
	char* block = (char*)malloc((sizeof(char) * (alen + blen)) + 1);
	for (int i = 0; i < alen; i++) {
		block[i] = a[i];
	}
	for (int i = 0; i < blen; i++) {
		block[alen + i] = b[i];
	}
	block[alen + blen] = '\0';
	return block;
}
