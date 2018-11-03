#include "line_range.h"
#include "../util/mem.h"

LineRange * NewLineRange() {
	LineRange* ret = (LineRange*)MEM_MALLOC(sizeof(LineRange));
	ret->StartOffset = -1;
	ret->EndOffset = -1;
	ret->Lineno = -1;
	return ret;
}

LineRange * FindLineRange(Vector * line_rangeVec, int pc) {
	for (int i = 0; i < line_rangeVec->Length; i++) {
		LineRange* lr = (LineRange*)AtVector(line_rangeVec, i);
		if (i >= lr->StartOffset && i <= lr->EndOffset) {
			return lr;
		}
	}
	return NULL;
}

void DeleteLineRange(LineRange * self) {
	MEM_FREE(self);
}
