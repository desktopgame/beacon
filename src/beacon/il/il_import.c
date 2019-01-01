#include "il_import.h"
#include <assert.h>
#include <stdlib.h>
#include "../util/mem.h"
#include "../util/text.h"

bc_ILImport* bc_NewILImport(bc_StringView path) {
        bc_ILImport* ret = (bc_ILImport*)MEM_MALLOC(sizeof(bc_ILImport));
        ret->Path = path;
        return ret;
}

void bc_DeleteILImport(bc_ILImport* self) {
        if (self == NULL) {
                return;
        }
        MEM_FREE(self);
}