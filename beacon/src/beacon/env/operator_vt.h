#ifndef BEACON_ENV_OPERATOR_VT_H
#define BEACON_ENV_OPERATOR_VT_H
#include "../util/vector.h"
struct OperatorOverload;

/**
 * オペレータの仮想関数テーブル.
 */
typedef struct OperatorVT {
	Vector* Operators;
} OperatorVT;

OperatorVT* NewOperatorVt();

void ReplaceOperatorVt(OperatorVT* self, struct OperatorOverload* opov);

void DeleteOperatorVt(OperatorVT* self);
#endif