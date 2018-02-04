#include "line_range.h"
#include "../util/mem.h"

line_range * line_range_new() {
	line_range* ret = (line_range*)MEM_MALLOC(sizeof(line_range));
	ret->start_offset = -1;
	ret->endOffset = -1;
	ret->lineno = -1;
	return ret;
}

void line_range_delete(line_range * self) {
	MEM_FREE(self);
}
