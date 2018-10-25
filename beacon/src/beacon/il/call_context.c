#include "call_context.h"
#include "../util/mem.h"
#include "../env/namespace.h"
#include "../env/method.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/generic_type.h"
#include "../env/fqcn_cache.h"

CallContext* MallocCContext(CallFrameTag tag, const char* filename, int lineno) {
	CallContext* ret = mem_malloc(sizeof(CallContext), filename, lineno);
#if defined(_MSC_VER)
	ControlStructure cs = { 0 };
#else
	ControlStructure cs = {};
#endif
	ret->CallStack = MallocVector(filename, lineno);
	ret->Scope = NULL;
	ret->Ty = NULL;
	ret->Tag = tag;
	ret->Control = cs;
	AllocControlStructure(&ret->Control);
	return ret;
}

CallFrame* PushImplCallContext(CallContext* self, CallFrameTag tag, const char* filename, int lineno) {
	CallFrame* fr = MallocCallFrame(tag, filename, lineno);
	PushVector(self->CallStack, fr);
	return fr;
}

CallFrame* TopCallContext(CallContext* self) {
	return TopVector(self->CallStack);
}

void PopCallContext(CallContext* self) {
	CallFrame* fr = PopVector(self->CallStack);
	DeleteCallFrame(fr);
}

namespace_* GetNamespaceCContext(CallContext* self) {
	if(self->Scope != NULL) {
		return self->Scope;
	}
	return GetLangNamespace();
}

Method* GetMethodCContext(CallContext* self) {
	if(self->Tag != CALL_METHOD_T) {
		return NULL;
	}
	return self->Kind.Method;
}

type* GetTypeCContext(CallContext* self) {
	if(self->Tag == CALL_TOP_T) {
		return FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	}
	return self->Ty;
}

class_* GetClassCContext(CallContext* self) {
	return TYPE2CLASS(GetTypeCContext(self));
}

generic_type* GetReceiverCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->CallStack);
	if(cfr->Tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->Kind.InstanceInvoke.Receiver;
	} else if(cfr->Tag == FRAME_SELF_INVOKE_T) {
		return self->Ty->generic_self;
	} else if(cfr->Tag == FRAME_RESOLVE_T) {
		return cfr->Kind.Resolve.GType;
	}
	return NULL;
}

type* GetEvalTypeCContext(CallContext* self, fqcn_cache* fqcn) {
	type* tp = GetTypeFQCN(fqcn, self->Scope);
	if(tp == NULL) {
		tp = GetTypeFQCN(fqcn, GetLangNamespace());
	}
	return tp;
}

Vector* GetTypeArgsCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->CallStack);
	if(cfr->Tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->Kind.InstanceInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_STATIC_INVOKE_T) {
		return cfr->Kind.StaticInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_SELF_INVOKE_T) {
		return cfr->Kind.SelfInvoke.TypeArgs;
	} else if(cfr->Tag == FRAME_RESOLVE_T) {
		return cfr->Kind.Resolve.TypeArgs;
	}
	return NULL;
}

bool IsStaticCContext(CallContext* self) {
	return self->Tag == CALL_METHOD_T &&
	       IsStaticModifier(self->Kind.Method->Modifier);
}

void DeleteCallContext(CallContext* self) {
	FreeControlStructure(self->Control);
	DeleteVector(self->CallStack, VectorDeleterOfNull);
	MEM_FREE(self);
}