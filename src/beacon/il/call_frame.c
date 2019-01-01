#include "call_frame.h"
#include "../env/generic_type.h"
#include "../util/mem.h"

bc_CallFrame* bc_NewCallFrame(bc_GenericType* receiver, bc_Vector* args,
                              bc_Vector* type_args) {
        bc_CallFrame* ret = MEM_MALLOC(sizeof(bc_CallFrame));
        ret->Receiver = receiver;
        ret->Args = args;
        ret->TypeArgs = type_args;
        return ret;
}

void bc_DeleteCallFrame(bc_CallFrame* self) {
        self->Receiver = NULL;
        MEM_FREE(self);
}