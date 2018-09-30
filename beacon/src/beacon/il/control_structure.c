#include "control_structure.h"

void AllocControlStructure(control_structure* self) {
	self->while_start = NewVector();
	self->while_end = NewVector();
}

void FreeControlStructure(control_structure self) {
	DeleteVector(self.while_start, VectorDeleterOfNull);
	DeleteVector(self.while_end, VectorDeleterOfNull);
}