#include "label.h"
#include <stdlib.h>

label * label_new(int cursor) {
	label* ret = (label*)malloc(sizeof(label));
	ret->cursor = cursor;
	return ret;
}

void label_delete(label * self) {
	free(self);
}
