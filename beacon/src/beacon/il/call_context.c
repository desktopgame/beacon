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
	ret->call_stack = MallocVector(filename, lineno);
	ret->scope = NULL;
	ret->ty = NULL;
	ret->tag = tag;
	ret->control = cs;
	AllocControlStructure(&ret->control);
	return ret;
}

CallFrame* PushImplCallContext(CallContext* self, CallFrameTag tag, const char* filename, int lineno) {
	CallFrame* fr = MallocCallFrame(tag, filename, lineno);
	PushVector(self->call_stack, fr);
	return fr;
}

CallFrame* TopCallContext(CallContext* self) {
	return TopVector(self->call_stack);
}

void PopCallContext(CallContext* self) {
	CallFrame* fr = PopVector(self->call_stack);
	DeleteCallFrame(fr);
}

namespace_* GetNamespaceCContext(CallContext* self) {
	if(self->scope != NULL) {
		return self->scope;
	}
	return GetLangNamespace();
}

method* GetMethodCContext(CallContext* self) {
	if(self->tag != CALL_METHOD_T) {
		return NULL;
	}
	return self->u.mt;
}

type* GetTypeCContext(CallContext* self) {
	if(self->tag == CALL_TOP_T) {
		return FindTypeFromNamespace(GetLangNamespace(), InternString("World"));
	}
	return self->ty;
}

class_* GetClassCContext(CallContext* self) {
	return TYPE2CLASS(GetTypeCContext(self));
}

generic_type* GetReceiverCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->call_stack);
	if(cfr->Tag == FRAME_INSTANCE_INVOKE_T) {
		return cfr->Kind.InstanceInvoke.Receiver;
	} else if(cfr->Tag == FRAME_SELF_INVOKE_T) {
		return self->ty->generic_self;
	} else if(cfr->Tag == FRAME_RESOLVE_T) {
		return cfr->Kind.Resolve.GType;
	}
	return NULL;
}

type* GetEvalTypeCContext(CallContext* self, fqcn_cache* fqcn) {
	type* tp = GetTypeFQCN(fqcn, self->scope);
	if(tp == NULL) {
		tp = GetTypeFQCN(fqcn, GetLangNamespace());
	}
	return tp;
}

Vector* GetTypeArgsCContext(CallContext* self) {
	CallFrame* cfr = TopVector(self->call_stack);
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
	return self->tag == CALL_METHOD_T &&
	       IsStaticModifier(self->u.mt->modifier);
}

void DeleteCallContext(CallContext* self) {
	FreeControlStructure(self->control);
	DeleteVector(self->call_stack, VectorDeleterOfNull);
	MEM_FREE(self);
}