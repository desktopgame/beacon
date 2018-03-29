#pragma once
#ifndef BEACON_IL_IL_PARAMETER_H
#define BEACON_IL_IL_PARAMETER_H
#include "../env/generic_cache.h"
//#include "il_type.h"
/**
 * パラメータの種類を表す列挙型.
 */
typedef enum il_parameter_type {
	il_param_type_default,
	il_param_type_ref,
	il_param_type_out,
} il_parameter_type;
/**
 * メソッド/関数の引数を表す要素.
 */
typedef struct il_parameter {
	il_parameter_type param_type;
	generic_cache* fqcn;
	char* name;
} il_parameter;
/**
 * パラメータを作成します.
 * @param name
 * @return
 */
il_parameter* il_parameter_new(const char* name);

/**
 * パラメータを出力します.
 * @param self
 * @param depth
 */
void il_parameter_dump(il_parameter* self, int depth);

/**
 * パラメータを開放します.
 * @param self
 */
void il_parameter_delete(il_parameter* self);
#endif // !SIGNAL_IL_IL_PARAMETER_H
