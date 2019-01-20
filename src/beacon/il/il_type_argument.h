// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_type_argument.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_TYPE_ARGUMENT_H
#define BEACON_IL_IL_TYPE_ARGUMENT_H
#include "../env/generic_cache.h"
#include "../env/generic_type.h"
#include "../util/vector.h"
struct bc_CallContext;

/**
 * 型実引数を表す構造体.
 */
typedef struct bc_ILTypeArgument {
        bc_GenericCache* GCache;
        bc_GenericType* GType;
} bc_ILTypeArgument;

/**
 * 新しい型実引数を作成します.
 * @return
 */
bc_ILTypeArgument* bc_NewILTypeArgument();

/**
 * @param iltype_args
 * @param cctx
 * @return
 */
void bc_ResolveILTypeArgument(bc_Vector* iltype_args,
                              struct bc_CallContext* cctx);

/**
 * 型実引数を解放します.
 * @param self
 */
void bc_DeleteILTypeArgument(bc_ILTypeArgument* self);
#endif
