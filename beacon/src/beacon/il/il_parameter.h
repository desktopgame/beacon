#pragma once
#ifndef BEACON_IL_IL_PARAMETER_H
#define BEACON_IL_IL_PARAMETER_H
#include "../env/generic_cache.h"
#include "../util/string_pool.h"
//#include "il_type.h"
/**
 * パラメータの種類を表す列挙型.
 */
typedef enum il_parameter_type {
	IL_PARAM_TYPE_DEFAULT,
	IL_PARAM_TYPE_REF_T,
	IL_PARAM_TYPE_OUT_T,
} il_parameter_type;
/**
 * メソッド/関数の引数を表す要素.
 */
typedef struct il_parameter {
	il_parameter_type param_type;
	generic_cache* fqcn;
	string_view namev;
} il_parameter;
/**
 * パラメータを作成します.
 * @param name
 * @return
 */
il_parameter* NewILParameter(string_view namev);

/**
 * パラメータを開放します.
 * @param self
 */
void DeleteILParameter(il_parameter* self);
#endif // !SIGNAL_IL_IL_PARAMETER_H
