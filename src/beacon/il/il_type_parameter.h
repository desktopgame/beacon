// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_type_parameter.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_TYPE_PARAMETER_H
#define BEACON_IL_IL_TYPE_PARAMETER_H
#include "../util/string_pool.h"
#include "../util/vector.h"

/**
 * 型引数の属性を表す列挙型.
 */
typedef enum bc_ILTypeParameterTag {
        IL_TYPE_PARAMETER_KIND_DEFAULT_T,
        IL_TYPE_PARAMETER_KIND_IN_T,
        IL_TYPE_PARAMETER_KIND_OUT_T,
} bc_ILTypeParameterTag;

/**
 * 型引数を表す構造体.
 */
typedef struct bc_ILTypeParameter {
        bc_ILTypeParameterTag Tag;
        bc_StringView Name;
} bc_ILTypeParameter;

/**
 * 新しい型引数を作成します.
 * @param name
 * @return
 */
bc_ILTypeParameter* bc_NewILTypeParameter(bc_StringView name);

/**
 * 型引数の一覧を出力します.
 * @param v<il_>
 */
void bc_PrintILTypeParameterList(bc_Vector* v);

/**
 * 型引数を解放します.
 * @param self
 */
void bc_DeleteILTypeParameter(bc_ILTypeParameter* self);
#endif  // !SIGNAL_IL_IL_TYPE_PARAMETER_H