#ifndef BEACON_IL_IL_FACTOR_MEMBER_OP_H
#define BEACON_IL_IL_FACTOR_MEMBER_OP_H
#include "../../env/fqcn_cache.h"
#include "../../util/vector.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

#define IL_FACT2MEM(fact) (il_factor_cast_member_op(fact))

struct enviroment;
struct field;

/**
 * メンバアクセスを表す要素.
 */
typedef struct il_factor_member_op {
	il_factor* fact;
	char* name;
	vector* type_args;
	int index;
	struct field* f;
} il_factor_member_op;

/**
 * メンバアクセスを表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_member_op(il_factor_member_op* self);
/**
 * メンバアクセスを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_member_op* il_factor_member_op_new(const char* name);

/**
 * メンバアクセスを表す要素をダンプします.
 * @param self
 * @param depth
 */
void il_factor_member_op_dump(il_factor_member_op* self, int depth);

/**
 * メンバアクセスを表す要素を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_member_op_load(il_factor_member_op* self, struct enviroment* env, il_context* ilctx, il_ehandler* eh);

/**
 * メンバアクセスを出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_member_op_generate(il_factor_member_op* self, struct enviroment* env, il_context* ilctx);

/**
 * メンバアクセスを表す要素の型を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
generic_type* il_factor_member_op_eval(il_factor_member_op* self, struct enviroment* env, il_context* ilctx);

/**
 * メンバアクセスを表す要素を解放します.
 * @param self
 */
void il_factor_member_op_delete(il_factor_member_op* self);

il_factor_member_op* il_factor_cast_member_op(il_factor* fact);
#endif