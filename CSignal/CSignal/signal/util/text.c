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

char * text_strdup(const char * source) {
#if defined(_MSC_VER)
	return _strdup(source);
#else
	return strdup(source);
#endif
}
