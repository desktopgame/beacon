#include "il_argument.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../util/mem.h"
#include "../util/text.h"

bc_ILArgument* bc_NewILArgument() {
        void* block = MEM_MALLOC(sizeof(bc_ILArgument));
        assert(block != NULL);
        bc_ILArgument* ret = (bc_ILArgument*)block;
        ret->Factor = NULL;
        return ret;
}

void bc_DeleteILArgument(bc_ILArgument* self) {
        bc_DeleteILFactor(self->Factor);
        MEM_FREE(self);
}
