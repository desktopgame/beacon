#include "system.h"
#include <stdlib.h>

void system_exit(int status) {
	exit(status);
}

void system_abort() {
	abort();
}