#include "resolve.h"
#include "../../il/il_argument.h"
#include "../../il/il_type_argument.h"
#include "../parameter.h"
#include "../type_parameter.h"
// private
static bool match_option(bc_AccessLevel access, bc_SearchOption option);
static int calc_argument_distance(bc_Method* method, bc_Vector* args,
                                  bc_Vector* type_args);

bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name,
                         bc_Vector* args, bc_Vector* type_args,
                         bc_ExecutePhase phase, bc_SearchOption option,
                         int* outIndex) {
        (*outIndex) = -1;
        bc_Method* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < methods->Length; i++) {
                bc_Method* e = bc_AtVector(methods, i);
                //名前、引数の個数、型引数の数で判別する
                if (name != e->Name || args->Length != e->Parameters->Length ||
                    type_args->Length != e->TypeParameters->Length) {
                        continue;
                }
                //検索オプションにマッチしない
                if (match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(e, args, type_args);
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                }
        }
        return ret;
}
// private
static bool match_option(bc_AccessLevel access, bc_SearchOption option) {
        if (option == MATCH_ALL) {
                return true;
        }
        switch (access) {
                case ACCESS_PUBLIC_T:
                        return option == MATCH_PUBLIC_ONLY ||
                               option == MATCH_PUBLIC_OR_PROTECTED;
                case ACCESS_PRIVATE_T:
                        return false;
                case ACCESS_PROTECTED_T:
                        return option == MATCH_PUBLIC_OR_PROTECTED;
        }
        return false;
}

static int calc_argument_distance(bc_Method* method, bc_Vector* args,
                                  bc_Vector* type_args) {
        int sumDistance = 0;
        for (int i = 0; i < method->Parameters->Length; i++) {
                bc_Parameter* parameter = bc_AtVector(method->Parameters, i);
                bc_GenericType* argument = bc_AtVector(args, i);
                int distance =
                    bc_RdistanceGenericType(parameter->GType, argument);
                if (distance == -1) {
                        sumDistance = -1;
                        break;
                }
                sumDistance += distance;
        }
        return sumDistance;
}