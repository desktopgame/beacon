#ifndef BEACON_ENV_OPERATOR_OVERLOAD_H
#define BEACON_ENV_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
struct type;
struct Enviroment;
struct GenericType;
struct Frame;
/**
 * 演算子オーバーロードを表す構造体.
 */
typedef struct OperatorOverload {
	struct type* Parent;
	struct GenericType* ReturnGType;
	OperatorType Type;
	Vector* Parameters;
	struct Enviroment* Env;
	AccessLevel Access;
} OperatorOverload;

/**
 * 新しい演算子オーバーロードを生成します.
 * @param type
 * @return
 */
OperatorOverload* NewOperatorOverload(OperatorType type);

/**
 * 演算子オーバーロードを実行します.
 * @param self
 * @param fr
 * @param env
 */
void ExecuteOperatorOverload(OperatorOverload* self, struct Frame* fr, struct Enviroment* env);

/**
 * 演算子オーバーロードを解放します.
 * @param self
 */
void DeleteOperatorOverload(OperatorOverload* self);
#endif