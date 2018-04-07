#ifndef BEACON_IL_IL_TYPE_ARGUMENT_H
#define BEACON_IL_IL_TYPE_ARGUMENT_H
#include "../env/generic_cache.h"
#include "../util/vector.h"

/**
 * 型実引数を表す構造体.
 */
typedef struct il_type_argument {
	generic_cache* gcache;
} il_type_argument;

/**
 * 新しい型実引数を作成します.
 * @return
 */
il_type_argument* il_type_argument_new();

/**
 * 全ての型実引数を出力します.
 * @param iltype_args
 */
void il_type_argument_print(vector* iltype_args);

/**
 * 型実引数を解放します.
 * @param self
 */
void il_type_argument_delete(il_type_argument* self);
#endif
