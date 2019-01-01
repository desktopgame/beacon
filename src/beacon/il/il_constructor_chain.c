#include "il_constructor_chain.h"
#include <stdio.h>
#include "../util/mem.h"
#include "../util/text.h"
#include "il_argument.h"

// proto
static void ILConstructor_argument_delete(bc_VectorItem item);

bc_ILConstructorChain* bc_NewILConstructorChain() {
        bc_ILConstructorChain* ret =
            (bc_ILConstructorChain*)MEM_MALLOC(sizeof(bc_ILConstructorChain));
        ret->Type = CHAIN_TYPE_THIS_T;
        ret->Arguments = bc_NewVector();
        ret->Constructor = NULL;
        ret->ConstructorIndex = -1;
        return ret;
}

void bc_DeleteILConstructorChain(bc_ILConstructorChain* self) {
        if (self == NULL) {
                return;
        }
        bc_DeleteVector(self->Arguments, ILConstructor_argument_delete);
        MEM_FREE(self);
}
// private
static void ILConstructor_argument_delete(bc_VectorItem item) {
        bc_ILArgument* e = (bc_ILArgument*)item;
        bc_DeleteILArgument(e);
}