#pragma once
#ifndef BEACON_ENV_PARAMETER_H
#define BEACON_ENV_PARAMETER_H
#include "../util/string_pool.h"
#include "../util/vector.h"
//#include "virtual_type.h"
/**
 * メソッドの仮引数を表す構造体です.
 */
typedef struct Parameter {
	StringView Name;
	struct generic_type* GType;
} Parameter;

/**
 * 新しいパラメータを作成します.
 * @param namev
 * @return
 */
Parameter* NewParameter(StringView namev);

/**
 * パラメータを開放します.
 * @param self
 */
void DeleteParameter(Parameter* self);

/**
 * 重複するパラメータ名が存在するなら true.
 * @param parameters
 * @param namev
 * @return
 */
bool IsOverwrappedParameterName(Vector* parameters, StringView* namev);
#endif // !SIGNAL_ENV_PARAMETER_H
