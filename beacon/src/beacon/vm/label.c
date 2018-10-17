#include "label.h"
#include <stdlib.h>
#include "../util/mem.h"

Label * NewLabel(int cursor) {
	Label* ret = (Label*)MEM_MALLOC(sizeof(Label));
	ret->Cursor = cursor;
	return ret;
}

Label * CloneLabel(Label * src) {
	Label* ret = NewLabel(src->Cursor);
	return ret;
}

void DeleteLabel(Label * self) {
	MEM_FREE(self);
}
