//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_operator_overload.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_OPERATOR_OVERLOAD_H
#define BEACON_IL_IL_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../env/generic_cache.h"
#include "il_type_interface.h"
#include "../ast/access_level.h"
typedef struct ILOperatorOverload {
	OperatorType Type;
	Vector* Parameters;
	Vector* Statements;
	GenericCache* ReturnGCache;
	bc_AccessLevel Access;
} ILOperatorOverload;

ILOperatorOverload* NewILOperatorOverload(OperatorType type);

void DeleteILOperatorOverload(ILOperatorOverload* self);
#endif