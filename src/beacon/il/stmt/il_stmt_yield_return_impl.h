// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_yield_return_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_YIELD_RETURN_H
#define BEACON_IL_YIELD_RETURN_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

typedef struct bc_ILYieldReturn {
        bc_ILFactor* Value;
} bc_ILYieldReturn;

bc_ILStatement* bc_WrapILYieldReturn(bc_ILYieldReturn* self);

#define bc_NewILYieldReturn() (bc_MallocILYieldReturn(__FILE__, __LINE__))
bc_ILYieldReturn* bc_MallocILYieldReturn(const char* filename, int lineno);

void bc_GenerateILYieldReturn(bc_ILYieldReturn* self, bc_Enviroment* env,
                              bc_CallContext* cctx);

void bc_LoadILYieldReturn(bc_ILYieldReturn* self, bc_Enviroment* env,
                          bc_CallContext* cctx);

void bc_DeleteILYieldReturn(bc_ILYieldReturn* self);
#endif