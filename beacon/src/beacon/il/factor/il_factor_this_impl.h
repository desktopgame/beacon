//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_this_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_THIS_H
#define BEACON_IL_IL_FACTOR_THIS_H
#include "../../env/generic_type.h"
#include "../call_context.h"
struct bc_Enviroment;
struct bc_Type;
/**
 * thisを表す要素.
 */
typedef struct ILThis {
	bc_GenericType* Resolved;
} ILThis;

ILThis* NewILThis();

void GenerateILThis(ILThis* self, struct bc_Enviroment* env, CallContext* cctx);

void LoadILThis(ILThis* self, struct bc_Enviroment* env, CallContext* cctx);

bc_GenericType* EvalILThis(ILThis* self, struct bc_Enviroment* env, CallContext* cctx);

char* ILThisToString(ILThis* self, struct bc_Enviroment* env);

void DeleteILThis(ILThis* self);
#endif // !SIGNAL_IL_IL_FACTOR_THIS_H
