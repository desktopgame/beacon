#pragma once
#ifndef BEACON_VM_TRACE_H
#define BEACON_VM_TRACE_H
#include <stdint.h>
struct vm;

typedef struct vm_trace {
	struct vm* v;
	int32_t pc;
	int32_t jump_level;
} vm_trace;

vm_trace* vm_trace_new(struct vm* v);

void vm_trace_delete(vm_trace* self);
#endif // !SIGNAL_VM_TRACE_H
