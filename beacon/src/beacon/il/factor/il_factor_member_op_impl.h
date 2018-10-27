#ifndef BEACON_IL_IL_FACTOR_MEMBER_OP_H
#define BEACON_IL_IL_FACTOR_MEMBER_OP_H
#include "../../env/fqcn_cache.h"
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct Enviroment;
struct Field;

/**
 * メンバアクセスを表す要素.
 */
typedef struct ILFactor_member_op {
	ILFactor* parent;
	ILFactor* fact;
	StringView namev;
	Vector* type_args;
	int index;
	struct Field* f;
} ILFactor_member_op;

ILFactor* WrapILMemberOp(ILFactor_member_op* self);

ILFactor_member_op* NewILMemberOp(StringView namev);

void LoadILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx);

void GenerateILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILMemberOp(ILFactor_member_op* self, Enviroment* env, CallContext* cctx);

char* ILMemberOpToString(ILFactor_member_op* self, Enviroment* env);

void DeleteILMemberOp(ILFactor_member_op* self);

#endif