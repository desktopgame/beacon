#include "vm_trace.h"
#include "vm.h"
#include "../util/mem.h"

vm_trace * vm_trace_new(vm * v) {
	vm_trace* ret = (vm_trace*)MEM_MALLOC(sizeof(vm_trace));
	ret->v = v;
	ret->pc = -1;
	return ret;
}

void vm_trace_delete(vm_trace * self) {
	MEM_FREE(self);
}
