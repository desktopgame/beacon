#include "call_context.h"
#include "../env/TYPE_IMPL.h"
#include "../env/constructor.h"
#include "../env/fqcn_cache.h"
#include "../env/generic_type.h"
#include "../env/method.h"
#include "../env/namespace.h"
#include "../env/operator_overload.h"
#include "../env/type_interface.h"
#include "../util/mem.h"

bc_CallContext* bc_NewCallContext(bc_CallContextTag tag) {
        bc_CallContext* ret = MEM_MALLOC(sizeof(bc_CallContext));
#if defined(_MSC_VER)
        bc_ControlStructure cs = {0};
#else
        bc_ControlStructure cs = {};
#endif
        ret->CallStack = bc_NewVector();
        ret->Scope = NULL;
        ret->Ty = NULL;
        ret->Tag = tag;
        ret->Control = cs;
        bc_AllocControlStructure(&ret->Control);
        return ret;
}

bc_CallContext* bc_NewTopContext(bc_Type* worldType) {
        bc_CallContext* ret = bc_NewCallContext(CALL_TOP_T);
        ret->Scope = bc_GetLangNamespace(NULL);
        ret->Ty = worldType;
        return ret;
}

bc_CallContext* bc_NewMethodContext(bc_Method* method) {
        bc_CallContext* ret = bc_NewCallContext(CALL_METHOD_T);
        ret->Scope = BC_MEMBER_TYPE(method)->Location;
        ret->Ty = BC_MEMBER_TYPE(method);
        ret->Kind.Method = method;
        return ret;
}

bc_CallContext* bc_NewConstructorContext(bc_Constructor* ctor) {
        bc_CallContext* ret = bc_NewCallContext(CALL_CTOR_T);
        ret->Scope = BC_MEMBER_TYPE(ctor)->Location;
        ret->Ty = BC_MEMBER_TYPE(ctor);
        ret->Kind.Ctor = ctor;
        return ret;
}

bc_CallContext* bc_NewOperatorOverloadContext(bc_OperatorOverload* opov) {
        bc_CallContext* ret = bc_NewCallContext(CALL_OPOV_T);
        ret->Scope = BC_MEMBER_TYPE(opov)->Location;
        ret->Ty = BC_MEMBER_TYPE(opov);
        ret->Kind.OpOv = opov;
        return ret;
}

bc_CallContext* bc_NewNameContext(bc_Namespace* scope, bc_Type* type) {
        bc_CallContext* ret = bc_NewCallContext(CALL_DECL_T);
        ret->Scope = scope;
        ret->Ty = type;
        return ret;
}

bc_CallFrame* bc_PushCallFrame(bc_CallContext* self, bc_GenericType* receiver,
                               bc_Vector* args, bc_Vector* type_args) {
        bc_CallFrame* fr = bc_NewCallFrame(receiver, args, type_args);
        bc_PushVector(self->CallStack, fr);
        return fr;
}

bc_CallFrame* bc_TopCallFrame(bc_CallContext* self) {
        return bc_TopVector(self->CallStack);
}

void bc_PopCallFrame(bc_CallContext* self) {
        bc_CallFrame* fr = bc_PopVector(self->CallStack);
        bc_DeleteCallFrame(fr);
}

bc_Namespace* bc_GetNamespaceByContext(bc_CallContext* self) {
        if (self->Scope != NULL) {
                return self->Scope;
        }
        return bc_GetLangNamespace(NULL);
}

bc_Method* bc_GetMethodByContext(bc_CallContext* self) {
        if (self->Tag != CALL_METHOD_T) {
                return NULL;
        }
        return self->Kind.Method;
}

bc_Type* bc_GetTypeByContext(bc_CallContext* self) {
        if (self->Tag == CALL_TOP_T) {
                return bc_FindTypeFromNamespace(bc_GetLangNamespace(NULL),
                                                bc_InternString("World"));
        }
        return self->Ty;
}

bc_Class* bc_GetClassByContext(bc_CallContext* self) {
        return BC_TYPE2CLASS(bc_GetTypeByContext(self));
}

bc_GenericType* bc_GetCompileTimeReceiver(bc_CallContext* self) {
        if (self->CallStack->Length == 0) {
                return bc_GetTypeByContext(self)->GenericSelf;
        }
        bc_CallFrame* cfr = bc_TopVector(self->CallStack);
        return cfr->Receiver;
}

bc_Type* bc_ResolveContext(bc_CallContext* self, bc_FQCNCache* fqcn) {
        bc_Type* tp = bc_GetTypeFQCN(fqcn, self->Scope);
        if (tp == NULL) {
                tp = bc_GetTypeFQCN(fqcn, bc_GetLangNamespace(NULL));
        }
        return tp;
}

bc_Vector* bc_GetCompileTimeTypeArguments(bc_CallContext* self) {
        if (self->CallStack->Length == 0) {
                return bc_GetTypeByContext(self)->GenericSelf->TypeArgs;
        }
        bc_CallFrame* cfr = bc_TopVector(self->CallStack);
        return cfr->TypeArgs;
}

bool bc_IsStaticContext(bc_CallContext* self) {
        return self->Tag == CALL_METHOD_T &&
               bc_IsStaticModifier(BC_MEMBER_MODIFIER(self->Kind.Method));
}

void bc_DeleteCallContext(bc_CallContext* self) {
        bc_FreeControlStructure(self->Control);
        bc_DeleteVector(self->CallStack, bc_VectorDeleterOfNull);
        MEM_FREE(self);
}