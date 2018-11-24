// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_throw_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_STM_THROW_H
#define BEACON_IL_IL_STM_THROW_H
#include "../il_factor_interface.h"
#include "../il_stmt_interface.h"

struct bc_Enviroment;

typedef struct bc_ILThrow {
        bc_ILFactor* Factor;
} bc_ILThrow;

bc_ILStatement* bc_WrapILThrow(bc_ILThrow* self);

bc_ILThrow* bc_NewILThrow();

void bc_GenerateILThrow(bc_ILThrow* self, bc_Enviroment* env,
                        bc_CallContext* cctx);

void bc_LoadILThrow(bc_ILThrow* self, bc_Enviroment* env, bc_CallContext* cctx);

void bc_DeleteILThrow(bc_ILThrow* self);
#endif
