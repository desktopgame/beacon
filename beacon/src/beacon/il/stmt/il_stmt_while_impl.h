//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_while_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_STMT_WHILE_H
#define BEACON_IL_IL_STMT_WHILE_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"
#include "../../util/vector.h"

struct bc_Enviroment;

typedef struct ILWhile {
	ILFactor* Condition;
	Vector* Statements;
} ILWhile;

ILStatement* WrapILWhile(ILWhile* self);

ILWhile* NewILWhile();

void GenerateILWhile(ILWhile* self, bc_Enviroment* env, CallContext* cctx);

void LoadILWhile(ILWhile* self, bc_Enviroment* env, CallContext* cctx);

void DeleteILWhile(ILWhile* self);
#endif // !SIGNAL_IL_IL_STMT_WHILE_H
