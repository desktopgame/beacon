// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_string_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_STRING_H
#define BEACON_IL_IL_FACTOR_STRING_H
#include "../../util/string_pool.h"
#include "../il_factor_interface.h"

// struct opcode_buf;
/**
 * 文字列を表す要素.
 */
typedef struct bc_ILString {
        bc_StringView Value;
} bc_ILString;

bc_ILFactor* bc_WrapILString(bc_ILString* self);

bc_ILString* bc_NewILString(bc_StringView valuev);

void bc_GenerateILString(bc_ILString* self, bc_Enviroment* env,
                         bc_CallContext* cctx);

void bc_LoadILString(bc_ILString* self, bc_Enviroment* env,
                     bc_CallContext* cctx);

bc_GenericType* bc_EvalILString(bc_ILString* self, bc_Enviroment* env,
                                bc_CallContext* cctx);

char* bc_ILStringToString(bc_ILString* self, bc_Enviroment* env);

void bc_DeleteILString(bc_ILString* self);

#endif  // !SIGNAL_IL_IL_FACTOR_STRING_H
