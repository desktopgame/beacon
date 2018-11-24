// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_char_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_CHAR_H
#define BEACON_IL_IL_FACTOR_CHAR_H
#include "../il_factor_interface.h"

// struct opcode_buf;
/**
 * 文字を表す要素.
 */
typedef struct bc_ILChar {
        char Value;
} bc_ILChar;

bc_ILFactor* bc_WrapILChar(bc_ILChar* self);

bc_ILChar* bc_NewILChar(char c);

void bc_GenerateILChar(bc_ILChar* self, bc_Enviroment* env,
                       bc_CallContext* cctx);

void bc_LoadILChar(bc_ILChar* self, bc_Enviroment* env, bc_CallContext* cctx);

bc_GenericType* bc_EvalILChar(bc_ILChar* self, bc_Enviroment* env,
                              bc_CallContext* cctx);

char* bc_ILCharToString(bc_ILChar* self, bc_Enviroment* env);

void bc_DeleteILChar(bc_ILChar* self);

#endif  // !SIGNAL_IL_IL_FACTOR_CHAR_H
