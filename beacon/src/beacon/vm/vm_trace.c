#include "vm_trace.h"
#include "frame.h"
#include "../util/mem.h"

VMTrace * NewVMTrace(frame * snapShot) {
	VMTrace* ret = (VMTrace*)MEM_MALLOC(sizeof(VMTrace));
	ret->SnapShot = snapShot;
	ret->PC = -1;
	ret->JumpLevel = 0;
	return ret;
}

void DeleteVMTrace(VMTrace * self) {
	MEM_FREE(self);
}
