#include "control_structure.h"

void control_structure_alloc(control_structure* self) {
	self->while_start = vector_new();
	self->while_end = vector_new();
}

void control_structure_free(control_structure self) {
	vector_delete(self.while_start, vector_deleter_null);
	vector_delete(self.while_end, vector_deleter_null);
}