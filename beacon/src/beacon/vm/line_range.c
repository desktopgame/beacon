#include "line_range.h"
#include "../util/mem.h"

line_range * NewLineRange() {
	line_range* ret = (line_range*)MEM_MALLOC(sizeof(line_range));
	ret->start_offset = -1;
	ret->end_offset = -1;
	ret->lineno = -1;
	return ret;
}

line_range * FindLineRange(Vector * line_rangeVec, int pc) {
	for (int i = 0; i < line_rangeVec->Length; i++) {
		line_range* lr = (line_range*)AtVector(line_rangeVec, i);
		if (i >= lr->start_offset && i <= lr->end_offset) {
			return lr;
		}
	}
	return NULL;
}

void DeleteLineRange(line_range * self) {
	MEM_FREE(self);
}
