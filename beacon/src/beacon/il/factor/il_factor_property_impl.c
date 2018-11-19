#include "il_factor_property_impl.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../vm/generate.h"
#include "../../env/generic_type.h"
#include "../../env/field.h"
#include "../../env/TYPE_IMPL.h"
#include <assert.h>


ILPropertyAccess* MallocILPropertyAccess(const char* filename, int lineno) {
	ILPropertyAccess* ret = bc_MXMalloc(sizeof(ILPropertyAccess), filename, lineno);
	ret->Source = NULL;
	ret->Index = -1;
	ret->Name = ZERO_VIEW;
	ret->Property = NULL;
	return ret;
}

void GenerateILPropertyAccess(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	GenerateILFactor(self->Source, env, cctx);
	GenerateGetProperty(env->Bytecode, self->Property, self->Index);
}

void LoadILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	bc_GenericType* receiver = EvalILFactor(self->Source, env, cctx);
	bc_Type* receiverT = bc_GENERIC2TYPE(receiver);
	int temp = -1;
	FindTreePropertyClass(BC_TYPE2CLASS(receiverT), self->Property->Name, &temp);
	self->Index = temp;
	if(temp == -1) {
		bc_Panic(
			BCERROR_UNDEFINED_PROPERTY_T,
			Ref2Str(bc_GetTypeName(receiverT)),
			Ref2Str(self->Name)
		);
	}
}

bc_GenericType* EvalILProperty(ILPropertyAccess* self, Enviroment* env, CallContext* cctx) {
	return self->Property->GType;
}

char* ILPropertyToString(ILPropertyAccess* self, Enviroment* env) {
	Buffer* sb = NewBuffer();
	char* name = ILFactorToString(self->Source, env);
	AppendsBuffer(sb, name);
	AppendBuffer(sb, '.');
	AppendsBuffer(sb, Ref2Str(self->Name));
	MEM_FREE(name);
	return ReleaseBuffer(sb);
}

void DeleteILPropertyAccess(ILPropertyAccess* self) {
	DeleteILFactor(self->Source);
	MEM_FREE(self);
}