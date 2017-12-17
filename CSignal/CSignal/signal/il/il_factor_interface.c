#include "il_factor_interface.h"
#include "../util/text.h"
#include <stdio.h>

void il_factor_dump(il_factor * self, int depth) {
	if (self == NULL) {
		text_putindent(depth);
		printf("c-null");
		text_putline();
	}
}

void il_factor_delete(il_factor * self) {
}
