#include "resolve.h"

bc_Method* bc_resolve_FindMethod(bc_Vector* methods, bc_StringView name,
                                 bc_Vector* args, bc_Vector* type_args,
                                 bc_ExecutePhase phase) {
        for (int i = 0; i < methods->Length; i++) {
                bc_Method* e = bc_AtVector(methods, i);
                if (e->Name != name) {
                        continue;
                }
                if (e->Parameters->Length != args->Length) {
                        continue;
                }
                if (e->TypeParameters->Length != type_args->Length) {
                        continue;
                }
        }
}
// private
