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

il_type* WrapILEnum(il_enum* self);

il_enum* NewILEnum(string_view namev);

void DeleteILEnum(il_enum* self);
#endif // !SIGNAL_IL_IL_ENUM_H
