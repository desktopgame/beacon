#include "control_structure.h"

void AllocControlStructure(ControlStructure* self) {
	self->WhileStartTable = NewVector();
	self->WhileEndTable = NewVector();
}

void FreeControlStructure(ControlStructure self) {
	DeleteVector(self.WhileStartTable, VectorDeleterOfNull);
	DeleteVector(self.WhileEndTable, VectorDeleterOfNull);
}