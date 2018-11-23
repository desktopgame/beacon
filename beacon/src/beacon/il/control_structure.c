#include "control_structure.h"

void bc_AllocControlStructure(bc_ControlStructure* self) {
        self->WhileStartTable = bc_NewVector();
        self->WhileEndTable = bc_NewVector();
}

void bc_FreeControlStructure(bc_ControlStructure self) {
        bc_DeleteVector(self.WhileStartTable, bc_VectorDeleterOfNull);
        bc_DeleteVector(self.WhileEndTable, bc_VectorDeleterOfNull);
}