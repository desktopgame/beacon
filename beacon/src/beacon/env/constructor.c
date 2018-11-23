#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../vm/frame.h"
#include "../vm/vm.h"
#include "generic_type.h"
#include "object.h"
#include "parameter.h"
#include "type_interface.h"

// proto
static void delete_parameter(bc_VectorItem item);

bc_Constructor* bc_NewConstructor() {
        bc_Constructor* ret =
            (bc_Constructor*)MEM_MALLOC(sizeof(bc_Constructor));
        ret->Parent = NULL;
        ret->Env = NULL;
        ret->Parameters = bc_NewVector();
        ret->Access = ACCESS_PUBLIC_T;
        return ret;
}

bc_Object* bc_NewInstanceConstructor(bc_Constructor* self, bc_Vector* args,
                                     bc_Frame* parent) {
        bc_Frame* sub = bc_SubFrame(parent);
        for (int i = 0; i < args->Length; i++) {
                bc_PushVector(sub->ValueStack, bc_AtVector(args, i));
        }
        bc_ExecuteVM(sub, self->Env);
        bc_Object* ret = bc_PopVector(sub->ValueStack);
        bc_DeleteFrame(sub);
        return ret;
}

void bc_DeleteConstructor(bc_Constructor* self) {
        bc_DeleteEnviroment(self->Env);
        bc_DeleteVector(self->Parameters, delete_parameter);
        MEM_FREE(self);
}

// private
static void delete_parameter(bc_VectorItem item) {
        bc_Parameter* e = (bc_Parameter*)item;
        bc_DeleteParameter(e);
}