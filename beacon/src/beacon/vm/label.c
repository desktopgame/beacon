#include "label.h"
#include <stdlib.h>
#include "../util/mem.h"

label * NewLabel(int cursor) {
	label* ret = (label*)MEM_MALLOC(sizeof(label));
	ret->cursor = cursor;
	return ret;
}

label * CloneLabel(label * src) {
	label* ret = NewLabel(src->cursor);
	return ret;
}

void DeleteLabel(label * self) {
	MEM_FREE(self);
}
