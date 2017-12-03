#include "text.h"
#include <stdio.h>

void text_putline() {
#if defined(_WIN32)
	printf("\n");
#else
	printf("\n");
#endif // defined(_WIN32)

}