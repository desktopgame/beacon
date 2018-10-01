#pragma once
#ifndef BEACON_ENV_PARAMETER_H
#define BEACON_ENV_PARAMETER_H
#include "../util/string_pool.h"
#include "../util/vector.h"
//#include "virtual_type.h"
/**
 * メソッドの仮引数を表す構造体です.
 */
typedef struct parameter {
	string_view namev;
	struct generic_type* gtype;
} parameter;

/**
 * 新しいパラメータを作成します.
 * @param namev
 * @return
 */
parameter* NewParameter(string_view namev);

/**
 * パラメータを開放します.
 * @param self
 */
void DeleteParameter(parameter* self);

/**
 * 重複するパラメータ名が存在するなら true.
 * @param parameters
 * @param namev
 * @return
 */
bool IsOverwrappedParameterName(Vector* parameters, string_view* namev);
#endif // !SIGNAL_ENV_PARAMETER_H
