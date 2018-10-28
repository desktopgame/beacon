#include "il_factor_property_impl.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../env/generic_type.h"
#include "../../env/field.h"
#include "../../env/TYPE_IMPL.h"
#include <assert.h>


ILPropertyAccess* MallocILPropertyAccess(const char* filename, int lineno) {
	ILPropertyAccess* ret = mem_malloc(sizeof(ILPropertyAccess), filename, lineno);
	ret->fact = NULL;
	ret->index = -1;
	ret->namev = ZERO_VIEW;
	ret->p = NULL;
	return ret;
}

void GenerateILPropertyAccess(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	GenerateGetProperty(env->Bytecode, self->p, self->index);
}

void LoadILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	GenericType* receiver = EvalILFactor(self->fact, env, cctx);
	type* receiverT = GENERIC2TYPE(receiver);
	int temp = -1;
	FindTreePropertyClass(TYPE2CLASS(receiverT), self->p->Name, &temp);
	self->index = temp;
	if(temp == -1) {
		ThrowBCError(
			BCERROR_UNDEFINED_PROPERTY_T,
			Ref2Str(GetTypeName(receiverT)),
			Ref2Str(self->namev)
		);
	}
}

GenericType* EvalILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	return self->p->GType;
}

char* ILPropertyToString(ILPropertyAccess* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* name = ILFactorToString(self->fact, env);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->namev));
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILPropertyAccess(ILPropertyAccess* self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}