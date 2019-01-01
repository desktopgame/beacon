#include "type_cache.h"
#include "../util/mem.h"
#include "class_loader.h"
#include "cll/class_loader_bcload_impl.h"

bc_TypeCache* bc_NewTypeCache() {
        bc_TypeCache* ret = (bc_TypeCache*)MEM_MALLOC(sizeof(bc_TypeCache));
        ret->Context = NULL;
        ret->ILType = NULL;
        ret->Type = NULL;
        ret->Scope = NULL;
        ret->IsConsume = false;
        return ret;
}

bc_TypeCache* bc_InitTypeCache(bc_TypeCache* self, bc_ClassLoader* context,
                               bc_ILType* iltype, bc_Type* tp,
                               bc_Namespace* scope, bc_TypeCacheKind kind) {
        self->Context = context;
        self->ILType = iltype;
        self->Type = tp;
        self->Scope = scope;
        self->Kind = kind;
        return self;
}

void bc_DeleteTypeCache(bc_TypeCache* self) { MEM_FREE(self); }
