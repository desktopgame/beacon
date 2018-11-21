#include "call_frame.h"
#include "../util/mem.h"

bc_CallFrame* bc_MallocCallFrame(bc_CallFrameTag tag, const char* filename, int lineno) {
	bc_CallFrame* ret = bc_MXMalloc(sizeof(bc_CallFrame), filename, lineno);
	ret->Tag = tag;
	return ret;
}

void bc_DeleteCallFrame(bc_CallFrame* self) {
	MEM_FREE(self);
}