#pragma once
#ifndef SIGNAL_IL_IL_ENUM_H
#define SIGNAL_IL_IL_ENUM_H
#include "../../util/vector.h"
#include "../il_type_interface.h"

typedef struct il_enum {
	char* name;
	vector* item_vec;
} il_enum;

il_type* il_type_wrap_enum(il_enum* self);

il_enum* il_enum_new(const char* name);

void il_enum_dump(il_enum* self, int depth);

void il_enum_delete(il_enum* self);
#endif // !SIGNAL_IL_IL_ENUM_H
