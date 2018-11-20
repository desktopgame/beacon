#include "vm_trace.h"
#include "frame.h"
#include "../util/mem.h"

bc_VMTrace * bc_NewVMTrace(bc_Frame* snapShot) {
	bc_VMTrace* ret = (bc_VMTrace*)MEM_MALLOC(sizeof(bc_VMTrace));
	ret->SnapShot = snapShot;
	ret->PC = -1;
	ret->JumpLevel = 0;
	return ret;
}

void bc_DeleteVMTrace(bc_VMTrace * self) {
	MEM_FREE(self);
}
