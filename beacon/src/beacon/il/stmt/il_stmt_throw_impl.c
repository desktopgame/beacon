#include "il_stmt_throw_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

il_stmt* WrapILThrow(il_stmt_throw* self) {
	il_stmt* ret = il_stmt_new(ILSTMT_THROW_T);
	ret->u.throw_ = self;
	return ret;
}

il_stmt_throw* NewILThrow() {
	il_stmt_throw* ret = (il_stmt_throw*)MEM_MALLOC(sizeof(il_stmt_throw));
	ret->fact = NULL;
	return ret;
}

void GenerateILThrow(il_stmt_throw* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_THROW);
}

void LoadILThrow(il_stmt_throw* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->fact, env, cctx);
	generic_type* tgt = EvalILFactor(self->fact, env, cctx);
	if(DistanceGenericType(GENERIC_EXCEPTION, tgt, cctx) < 0) {
		if(tgt->core_type != NULL) {
			ThrowBCError(
				BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,
				Ref2Str(GetTypeName(tgt->core_type))
			);
		}
	}
}

void DeleteILThrow(il_stmt_throw* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}