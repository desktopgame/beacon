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
typedef struct ILMemberOp {
	ILFactor* Parent;
	ILFactor* Source;
	StringView Name;
	Vector* TypeArgs;
	int Index;
	struct Field* Field;
} ILMemberOp;

ILFactor* WrapILMemberOp(ILMemberOp* self);

ILMemberOp* NewILMemberOp(StringView namev);

void LoadILMemberOp(ILMemberOp* self, Enviroment* env, CallContext* cctx);

void GenerateILMemberOp(ILMemberOp* self, Enviroment* env, CallContext* cctx);

GenericType* EvalILMemberOp(ILMemberOp* self, Enviroment* env, CallContext* cctx);

char* ILMemberOpToString(ILMemberOp* self, Enviroment* env);

void DeleteILMemberOp(ILMemberOp* self);

#endif