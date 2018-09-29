#pragma once
#ifndef BEACON_IL_IL_ENUM_H
#define BEACON_IL_IL_ENUM_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../il_type_interface.h"

typedef struct il_enum {
	string_view namev;
	Vector* item_vec;
} il_enum;

il_type* il_type_wrap_enum(il_enum* self);

il_enum* il_enum_new(string_view namev);

void il_enum_delete(il_enum* self);
#endif // !SIGNAL_IL_IL_ENUM_H
