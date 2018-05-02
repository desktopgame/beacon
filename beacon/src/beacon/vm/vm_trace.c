#include "vm_trace.h"
#include "frame.h"
#include "../util/mem.h"

vm_trace * vm_trace_new(frame * fr) {
	vm_trace* ret = (vm_trace*)MEM_MALLOC(sizeof(vm_trace));
	ret->fr = fr;
	ret->pc = -1;
	ret->jump_level = 0;
	return ret;
}

void vm_trace_delete(vm_trace * self) {
	MEM_FREE(self);
}
