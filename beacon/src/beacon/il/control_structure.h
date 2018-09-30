#ifndef BEACON_IL_CONTROL_STRUCTURE_H
#define BEACON_IL_CONTROL_STRUCTURE_H
#include "../util/vector.h"

typedef struct control_structure {
	Vector* while_start;
	Vector* while_end;
} control_structure;

void AllocControlStructure(control_structure* self);

void FreeControlStructure(control_structure self);
#endif