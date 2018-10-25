#ifndef BEACON_IL_IL_TYPE_ARGUMENT_H
#define BEACON_IL_IL_TYPE_ARGUMENT_H
#include "../env/generic_cache.h"
#include "../env/generic_type.h"
#include "../util/vector.h"
struct CallContext;

/**
 * 型実引数を表す構造体.
 */
typedef struct ILTypeArgument {
	generic_cache* gcache;
	generic_type* gtype;
} ILTypeArgument;

/**
 * 新しい型実引数を作成します.
 * @return
 */
ILTypeArgument* NewILTypeArgument();

/**
 * 全ての型実引数を出力します.
 * @param iltype_args
 */
void PrintILTypeArgument(Vector* iltype_args);

/**
 * @param iltype_args
 * @param cctx
 * @return
 */
void ResolveILTypeArgument(Vector* iltype_args, struct CallContext* cctx);

/**
 * 型実引数を解放します.
 * @param self
 */
void DeleteILTypeArgument(ILTypeArgument* self);
#endif
