#include "call_frame.h"
#include "../util/mem.h"

CallFrame* MallocCallFrame(CallFrameTag tag, const char* filename, int lineno) {
	CallFrame* ret = mem_malloc(sizeof(CallFrame), filename, lineno);
	ret->Tag = tag;
	return ret;
}

void DeleteCallFrame(CallFrame* self) {
	MEM_FREE(self);
}