#include "property_body.h"
#include "../util/mem.h"
#include "../vm/enviroment.h"

bc_PropertyBody* bc_MallocPropertyBody(bc_PropertyBodyTag tag,
                                       const char* filename, int lineno) {
        bc_PropertyBody* ret =
            bc_MXMalloc(sizeof(bc_PropertyBody), filename, lineno);
        ret->Tag = tag;
        ret->Env = bc_NewEnviroment();
        ret->Parent = NULL;
        return ret;
}

void bc_DeletePropertyBody(bc_PropertyBody* self) {
        bc_DeleteEnviroment(self->Env);
        MEM_FREE(self);
}