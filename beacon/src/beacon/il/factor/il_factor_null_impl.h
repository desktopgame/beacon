//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_null_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_NULL_H
#define BEACON_IL_IL_FACTOR_NULL_H
#include "../il_factor_interface.h"

struct bc_Enviroment;
struct bc_Type;

void bc_GenerateILNull(void* empty, bc_Enviroment* env, bc_CallContext* cctx);

void bc_LoadILNull(void* empty, bc_Enviroment* env, bc_CallContext* cctx);

bc_GenericType* bc_EvalILNull(void* empty, bc_Enviroment* env, bc_CallContext* cctx);

char* bc_ILNullToString(void* empty, bc_Enviroment* env);
#endif // !SIGNAL_IL_IL_FACTOR_NULL_H
