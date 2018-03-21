#include "label.h"
#include <stdlib.h>
#include "../util/mem.h"

label * label_new(int cursor) {
	label* ret = (label*)MEM_MALLOC(sizeof(label));
	ret->cursor = cursor;
	return ret;
}

label * label_clone(label * src) {
	label* ret = label_new(src->cursor);
	return ret;
}

void label_delete(label * self) {
	MEM_FREE(self);
}
