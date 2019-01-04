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
        ret->Env = NULL;
        ret->Parameters = bc_NewVector();
        bc_InitMember((bc_Member*)ret);
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