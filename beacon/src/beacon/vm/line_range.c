#include "line_range.h"
#include "../util/mem.h"

bc_LineRange * bc_NewLineRange() {
	bc_LineRange* ret = (bc_LineRange*)MEM_MALLOC(sizeof(bc_LineRange));
	ret->StartOffset = -1;
	ret->EndOffset = -1;
	ret->Lineno = -1;
	return ret;
}

bc_LineRange * bc_FindLineRange(bc_Vector * line_rangeVec, int pc) {
	for (int i = 0; i < line_rangeVec->Length; i++) {
		bc_LineRange* lr = (bc_LineRange*)bc_AtVector(line_rangeVec, i);
		if (i >= lr->StartOffset && i <= lr->EndOffset) {
			return lr;
		}
	}
	return NULL;
}

void bc_DeleteLineRange(bc_LineRange * self) {
	MEM_FREE(self);
}
