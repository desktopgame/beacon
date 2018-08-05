#pragma once
#ifndef BEACON_ENV_TYPE_PARAMETER_H
#define BEACON_ENV_TYPE_PARAMETER_H
#include "../util/string_pool.h"
#include "../util/vector.h"
#include <stdbool.h>
struct vector;
struct il_type_parameter;
/**
 * 型変数の種類を表す列挙.
 */
typedef enum type_parameter_kind {
	type_parameter_kind_default,
	type_parameter_kind_in,
	type_parameter_kind_out,
} type_parameter_kind;

/**
 * 型変数を表す構造体.
 */
typedef struct type_parameter {
	string_view namev;
	type_parameter_kind kind;
//	struct vector* rule_vec;
} type_parameter;
/**
 * 新しい型変数を生成します.
 * @param name
 * @return
 */
type_parameter* type_parameter_new(string_view namev);

/**
 * ILから型変数を生成します.
 * @param src
 * @param return
 */
type_parameter* type_parameter_dup(struct il_type_parameter* src);

/**
 * ILから型変数を生成します.
 * @param ilSource
 * @param sgDest
 */
void type_parameter_list_dup(struct vector* ilSource, struct vector* sgDest);

/**
 * 型変数の一覧を出力します.
 * @param v
 */
void type_parameter_print(struct vector* v);

/**
 * 型変数を解放します.
 * @param self
 */
void type_parameter_delete(type_parameter* self);

/**
 * 重複するパラメータ名が存在するなら true.
 * @param tparameters
 * @param namev
 * @return
 */
bool type_parameter_is_overwrapped_name(vector* tparameters, string_view* namev);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_H
