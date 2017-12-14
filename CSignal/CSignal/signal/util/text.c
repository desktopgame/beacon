#include "text.h"
#include <stdio.h>
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
