#include "call_frame.h"
#include "../util/mem.h"

call_frame* MallocCallFrame(call_frame_tag tag, const char* filename, int lineno) {
	call_frame* ret = mem_malloc(sizeof(call_frame), filename, lineno);
	ret->tag = tag;
	return ret;
}

void DeleteCallFrame(call_frame* self) {
	MEM_FREE(self);
}