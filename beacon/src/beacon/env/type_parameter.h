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
typedef enum TypeParameterKind {
	TYPE_PARAMETER_KIND_DEFAULT_T,
	TYPE_PARAMETER_KIND_IN_T,
	TYPE_PARAMETER_KIND_OUT_T,
} TypeParameterKind;

/**
 * 型変数を表す構造体.
 */
typedef struct TypeParameter {
	StringView namev;
	TypeParameterKind kind;
//	struct Vector* rule_vec;
} TypeParameter;
/**
 * 新しい型変数を生成します.
 * @param name
 * @return
 */
TypeParameter* NewTypeParameter(StringView namev);

/**
 * ILから型変数を生成します.
 * @param src
 * @param return
 */
TypeParameter* DupTypeParameter(struct il_type_parameter* src);

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
void DeleteTypeParameter(TypeParameter* self);

/**
 * 重複するパラメータ名が存在するなら true.
 * @param tparameters
 * @param namev
 * @return
 */
bool IsOverwrappedTypeParameterName(Vector* tparameters, StringView* namev);
#endif // !SIGNAL_ENV_TYPE_PARAMETER_H
