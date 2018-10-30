#pragma once
#ifndef BEACON_ENV_FIELD_H
#define BEACON_ENV_FIELD_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
//#include "virtual_type.h"
struct Type;
struct GenericType;
struct Object;
struct Enviroment;
struct ILFactor;
/**
 * フィールドを表す構造体.
 */
typedef struct Field {
	StringView Name;
	struct Type* Parent;
	struct GenericType* GType;
	struct Object* StaticValue;
	AccessLevel Access;
	ModifierType Modifier;
	struct ILFactor* InitialValue;
	struct Enviroment* InitialValueEnv;
	bool IsNotInitializedAtCtor;
} Field;

/**
 * 新しいフィールドを作成します.
 * @param namev
 * @return
 */
Field* NewField(StringView namev);

/**
 * フィールドを開放します.
 * @param self
 */
void DeleteField(Field* self);
#endif // !SIGNAL_ENV_FIELD_H
