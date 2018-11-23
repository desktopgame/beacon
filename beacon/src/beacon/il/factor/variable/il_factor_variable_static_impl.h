//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_variable_static_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#define BEACON_IL_IL_FACTOR_VARIABLE_STATIC_H
#include "../../../env/fqcn_cache.h"
#include "../../il_factor_interface.h"
struct bc_Enviroment;
struct bc_GenericType;

typedef struct bc_ILVariableStatic {
	bc_FQCNCache* FQCN;
	bc_Vector* TypeArgs;
} bc_ILVariableStatic;

bc_ILVariableStatic* bc_NewILVariableStatic();

void bc_GenerateILVariableStatic(bc_ILVariableStatic* self, bc_Enviroment* env, bc_CallContext* cctx);

void bc_LoadILVariableStatic(bc_ILVariableStatic * self, bc_Enviroment * env, bc_CallContext* cctx);

struct bc_GenericType* bc_EvalILVariableStatic(bc_ILVariableStatic * self, bc_Enviroment * env, bc_CallContext* cctx);

char* bc_ILVariableStaticToString(bc_ILVariableStatic * self, bc_Enviroment * env);

void bc_DeleteILVariableStatic(bc_ILVariableStatic* self);
#endif