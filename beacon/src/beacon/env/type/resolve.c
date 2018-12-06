#include "resolve.h"
#include "../../il/il_argument.h"
#include "../../il/il_type_argument.h"
#include "../parameter.h"
#include "../type_impl.h"
#include "../type_parameter.h"
// private
static bool match_option(bc_AccessLevel access, bc_SearchOption option);
static int calc_argument_distance(bc_Vector* parameters, int args_count,
                                  bc_GenericType* args[], bc_Vector* type_args);

void bc_EvaluateArguments(bc_Vector* args, bc_GenericType* result[],
                          bc_Enviroment* env, bc_CallContext* cctx) {
        for (int i = 0; i < args->Length; i++) {
                bc_ILArgument* e = bc_AtVector(args, i);
                bc_GenericType* gtype = bc_EvalILFactor(e->Factor, env, cctx);
                result[i] = gtype;
        }
}

bc_OperatorOverload* bc_FindOperatorOverload(
    bc_Vector* operator_overloads, bc_OperatorType type, int args_count,
    bc_GenericType* args[], bc_SearchOption option, int* outIndex) {
        (*outIndex) = -1;
        bc_OperatorOverload* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < operator_overloads->Length; i++) {
                bc_OperatorOverload* e = bc_AtVector(operator_overloads, i);
                //種類か引数の数が違う
                if (e->Type != type || e->Parameters->Length != args_count) {
                        continue;
                }
                //検索オプションにマッチしない
                if (!match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(
                    e->Parameters, args_count, args, NULL);
                if (sumDistance == -1) {
                        continue;
                }
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                        (*outIndex) = i;
                }
        }
        return ret;
}

bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name, int args_count,
                         bc_GenericType* args[], bc_Vector* type_args,
                         bc_SearchOption option, int* outIndex) {
        (*outIndex) = -1;
        bc_Method* ret = NULL;
        int maxDistance = 1024;
        for (int i = 0; i < methods->Length; i++) {
                bc_Method* e = bc_AtVector(methods, i);
                //名前、引数の個数、型引数の数で判別する
                if (name != e->Name || args_count != e->Parameters->Length ||
                    type_args->Length != e->TypeParameters->Length) {
                        continue;
                }
                //検索オプションにマッチしない
                if (!match_option(BC_MEMBER_ACCESS(e), option)) {
                        continue;
                }
                int sumDistance = calc_argument_distance(
                    e->Parameters, args_count, args, type_args);
                if (sumDistance == -1) {
                        continue;
                }
                if (sumDistance < maxDistance) {
                        maxDistance = sumDistance;
                        ret = e;
                        (*outIndex) = i;
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

static int calc_argument_distance(bc_Vector* parameters, int args_count,
                                  bc_GenericType* args[],
                                  bc_Vector* type_args) {
        int sumDistance = 0;
        for (int i = 0; i < parameters->Length; i++) {
                bc_Parameter* parameter = bc_AtVector(parameters, i);
                bc_GenericType* argument = args[i];
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