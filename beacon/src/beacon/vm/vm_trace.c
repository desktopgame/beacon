#include "vm_trace.h"
#include "frame.h"
#include "../util/mem.h"

vm_trace * NewVMTrace(frame * fr) {
	vm_trace* ret = (vm_trace*)MEM_MALLOC(sizeof(vm_trace));
	ret->fr = fr;
	ret->pc = -1;
	ret->jump_level = 0;
	return ret;
}

void DeleteVMTrace(vm_trace * self) {
	MEM_FREE(self);
}
