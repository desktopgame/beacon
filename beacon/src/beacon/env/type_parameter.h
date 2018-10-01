#pragma once
#ifndef BEACON_ENV_TYPE_PARAMETER_H
#define BEACON_ENV_TYPE_PARAMETER_H
#include "../util/string_pool.h"
#include "../util/vector.h"
#include <stdbool.h>
struct il_type_parameter;
/**
 * 型変数の種類を表す列挙.
 */
typedef enum type_parameter_kind {
	TYPE_PARAMETER_KIND_DEFAULT_T,
	TYPE_PARAMETER_KIND_IN_T,
	TYPE_PARAMETER_KIND_OUT_T,
} type_parameter_kind;

/**
 * 型変数を表す構造体.
 */
typedef struct type_parameter {
	string_view namev;
	type_parameter_kind kind;
//	struct Vector* rule_vec;
} type_parameter;
/**
 * 新しい型変数を生成します.
 * @param name
 * @return
 */
type_parameter* NewTypeParameter(string_view namev);

/**
 * ILから型変数を生成します.
 * @param src
 * @param return
 */
type_parameter* DupTypeParameter(struct il_type_parameter* src);

/**
 * ILから型変数を生成します.
 * @param ilSource
 * @param sgDest
 */
void DupTypeParameterList(Vector* ilSource, Vector* sgDest);

/**
 * 型変数の一覧を出力します.
 * @param v
 */
void PrintTypeParameter(Vector* v);

/**
 * 型変数を解放します.
 * @param self
 */
void DeleteTypeParameter(type_parameter* self);

/**
 * 重複するパラメータ名が存在するなら true.
 * @param tparameters
 * @param namev
 * @return
 */
bool IsOverwrappedTypeParameterName(Vector* tparameters, string_view* namev);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_H
