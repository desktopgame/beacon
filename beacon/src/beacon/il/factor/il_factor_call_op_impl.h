#ifndef BEACON_IL_il_factor_call_op_H
#define BEACON_IL_il_factor_call_op_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "invoke/il_factor_invoke_impl.h"
#include "invoke/il_factor_invoke_static_impl.h"
#include "invoke/il_factor_invoke_bound_impl.h"

#define IL_FACT2CALL(fact) (il_factor_cast_call_op(fact))

struct enviroment;
struct generic_type;
/**
 * 関数呼び出し演算子の種類を表す列挙型.
 */
typedef enum ilcall_type {
	ilcall_type_invoke,
	ilcall_type_invoke_static,
	ilcall_type_invoke_bound,
	ilcall_type_undefined,
} ilcall_type;

/**
 * 関数呼び出し演算子を表す構造体.
 */
typedef struct il_factor_call_op {
	il_factor* parent;
	il_factor* receiver;
	//vector* type_argument_list;
	vector* argument_list;
	ilcall_type type;
	union {
		il_factor_invoke* invoke_;
		il_factor_invoke_static* invoke_static_;
		il_factor_invoke_bound* invoke_bound_;
	} u;
} il_factor_call_op;

/**
 * 関数呼び出し演算子をスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_call_op(il_factor_call_op* self);

/**
 * 新しい関数呼び出し演算子を作成します.
 * @return
 */
il_factor_call_op* il_factor_call_op_new();

/**
 * 関数呼び出し演算子をダンプします.
 * @param self
 * @param depth
 */
void il_factor_call_op_dump(il_factor_call_op* self, int depth);

/**
 * 関数呼び出し演算子を読み込みます.
 * @param self
 * @param env
 * @param ilctx
 * @param eh
 */
void il_factor_call_op_load(il_factor_call_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 関数呼び出し演算子の型を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
struct generic_type* il_factor_call_op_eval(il_factor_call_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 関数呼び出し演算子を出力します.
 * @param self
 * @param env
 * @param ilctx
 */
void il_factor_call_op_generate(il_factor_call_op* self, struct enviroment* env, il_context* ilctx);

/**
 * 関数呼び出し演算子を解放します.
 * @param self
 */
void il_factor_call_op_delete(il_factor_call_op* self);

il_factor_call_op* il_factor_cast_call_op(il_factor* fact);
#endif
