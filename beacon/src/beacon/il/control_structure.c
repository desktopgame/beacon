#include "control_structure.h"

void control_structure_alloc(control_structure* self) {
	self->while_start = NewVector();
	self->while_end = NewVector();
}

void control_structure_free(control_structure self) {
	DeleteVector(self.while_start, VectorDeleterOfNull);
	DeleteVector(self.while_end, VectorDeleterOfNull);
}