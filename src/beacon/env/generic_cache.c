#include "generic_cache.h"
#include <assert.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "TYPE_IMPL.h"
#include "generic_type.h"

// proto
static void tree_delete(bc_VectorItem item);

bc_GenericCache* bc_NewGenericCache() {
        bc_GenericCache* ret =
            (bc_GenericCache*)MEM_MALLOC(sizeof(bc_GenericCache));
        ret->FQCN = bc_NewFQCNCache();
        ret->TypeArgs = bc_NewVector();
        return ret;
}

char* bc_GenericCacheToString(bc_GenericCache* self) {
        bc_Buffer* sb = bc_NewBuffer();
        // Namespace::Class
        char* name = bc_FQCNCacheToString(self->FQCN);
        bc_AppendsBuffer(sb, name);
        // Namespace::Class[
        if (self->TypeArgs->Length > 0) {
                bc_AppendsBuffer(sb, "[");
        }
        // Namespace::Class[...
        for (int i = 0; i < self->TypeArgs->Length; i++) {
                bc_GenericCache* e =
                    (bc_GenericCache*)bc_AtVector(self->TypeArgs, i);
                char* type = bc_GenericCacheToString(e);
                bc_AppendsBuffer(sb, type);
                if (i != (self->TypeArgs->Length - 1)) {
                        bc_AppendsBuffer(sb, ", ");
                }
                MEM_FREE(type);
        }
        // Namespace::Class[...]
        if (self->TypeArgs->Length > 0) {
                bc_AppendsBuffer(sb, "]");
        }
        MEM_FREE(name);
        return bc_ReleaseBuffer(sb);
}

void bc_DeleteGenericCache(bc_GenericCache* self) {
        bc_DeleteFQCNCache(self->FQCN);
        bc_DeleteVector(self->TypeArgs, tree_delete);
        MEM_FREE(self);
}

// private
static void tree_delete(bc_VectorItem item) {
        bc_GenericCache* e = (bc_GenericCache*)item;
        bc_DeleteGenericCache(e);
}