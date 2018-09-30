#ifndef BEACON_IL_IL_TYPE_ARGUMENT_H
#define BEACON_IL_IL_TYPE_ARGUMENT_H
#include "../env/generic_cache.h"
#include "../env/generic_type.h"
#include "../util/vector.h"
struct call_context;

/**
 * 型実引数を表す構造体.
 */
typedef struct il_type_argument {
	generic_cache* gcache;
	generic_type* gtype;
} il_type_argument;

/**
 * 新しい型実引数を作成します.
 * @return
 */
il_type_argument* NewILTypeArgument();

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
void ResolveILTypeArgument(Vector* iltype_args, struct call_context* cctx);

/**
 * 型実引数を解放します.
 * @param self
 */
void DeleteILTypeArgument(il_type_argument* self);
#endif
