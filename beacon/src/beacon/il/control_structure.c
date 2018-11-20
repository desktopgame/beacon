#include "control_structure.h"

void AllocControlStructure(ControlStructure* self) {
	self->WhileStartTable = bc_NewVector();
	self->WhileEndTable = bc_NewVector();
}

void FreeControlStructure(ControlStructure self) {
	bc_DeleteVector(self.WhileStartTable, bc_VectorDeleterOfNull);
	bc_DeleteVector(self.WhileEndTable, bc_VectorDeleterOfNull);
}