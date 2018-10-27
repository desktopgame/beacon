#pragma once
#ifndef BEACON_IL_IL_ENUM_H
#define BEACON_IL_IL_ENUM_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../il_type_interface.h"

typedef struct ILEnum {
	StringView Name;
	Vector* Items;
} ILEnum;

ILType* WrapILEnum(ILEnum* self);

ILEnum* NewILEnum(StringView namev);

void DeleteILEnum(ILEnum* self);
#endif // !SIGNAL_IL_IL_ENUM_H
