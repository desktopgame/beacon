#include "il_stmt_throw_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

ILStatement* WrapILThrow(ILThrow* self) {
	ILStatement* ret = ILStatement_new(ILSTMT_THROW_T);
	ret->u.throw_ = self;
	return ret;
}

ILThrow* NewILThrow() {
	ILThrow* ret = (ILThrow*)MEM_MALLOC(sizeof(ILThrow));
	ret->fact = NULL;
	return ret;
}

void GenerateILThrow(ILThrow* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_THROW);
}

void LoadILThrow(ILThrow* self, Enviroment* env, CallContext* cctx) {
	LoadILFactor(self->fact, env, cctx);
	GenericType* tgt = EvalILFactor(self->fact, env, cctx);
	if(DistanceGenericType(GENERIC_EXCEPTION, tgt, cctx) < 0) {
		if(tgt->CoreType != NULL) {
			ThrowBCError(
				BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,
				Ref2Str(GetTypeName(tgt->CoreType))
			);
		}
	}
}

void DeleteILThrow(ILThrow* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}