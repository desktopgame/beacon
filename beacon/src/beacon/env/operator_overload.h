#ifndef BEACON_ENV_OPERATOR_OVERLOAD_H
#define BEACON_ENV_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
struct type;
struct enviroment;
struct generic_type;
struct frame;
/**
 * 演算子オーバーロードを表す構造体.
 */
typedef struct operator_overload {
	struct type* parent;
	struct generic_type* return_gtype;
	operator_type type;
	vector* parameter_list;
	struct enviroment* env;
	access_level access;
} operator_overload;

/**
 * 新しい演算子オーバーロードを生成します.
 * @param type
 * @return
 */
operator_overload* operator_overload_new(operator_type type);

/**
 * 演算子オーバーロードを実行します.
 * @param self
 * @param fr
 * @param env
 */
void operator_overload_execute(operator_overload* self, struct frame* fr, struct enviroment* env);

/**
 * 演算子オーバーロードを解放します.
 * @param self
 */
void operator_overload_delete(operator_overload* self);
#endif