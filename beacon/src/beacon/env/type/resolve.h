#ifndef BEACON_ENV_TYPE_RESOLVE_H
#define BEACON_ENV_TYPE_RESOLVE_H
#include "../../il/call_context.h"
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "../../vm/enviroment.h"
#include "../constructor.h"
#include "../field.h"
#include "../generic_type.h"
#include "../method.h"
#include "../operator_overload.h"
#include "../property.h"
#include "../type_interface.h"

typedef enum bc_SearchOption {
        MATCH_ALL,
        MATCH_PUBLIC_ONLY,
        MATCH_PUBLIC_OR_PROTECTED
} bc_SearchOption;

void bc_CevaluateArguments(bc_Vector* args, bc_GenericType* result[],
                           bc_Enviroment* env, bc_CallContext* cctx);

void bc_RevaluateArguments(bc_Vector* args, bc_GenericType* result[]);

//
// Find
//
bc_OperatorOverload* bc_FindOperatorOverload(
    bc_Vector* operator_overloads, bc_OperatorType type, int args_count,
    bc_GenericType* args[], bc_SearchOption option, bc_CallContext* cctx,
    int* outIndex);

bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name, int args_count,
                         bc_GenericType* args[], bc_Vector* type_args,
                         bc_SearchOption option, bc_CallContext* cctx,
                         int* outIndex);

bc_Constructor* bc_FindConstructor(bc_Vector* constructors, int args_count,
                                   bc_GenericType* args[], bc_Vector* type_args,
                                   bc_SearchOption option, bc_CallContext* cctx,
                                   int* outIndex);

bc_Field* bc_FindField(bc_Vector* fields, bc_StringView name,
                       bc_SearchOption option, int* outIndex);

bc_Property* bc_FindProperty(bc_Vector* properties, bc_StringView name,
                             bc_SearchOption option, int* outIndex);

//
// Resolve
//
bc_Field* bc_ResolveField(struct bc_Class* classz, bc_StringView name,
                          int* outIndex);

bc_Property* bc_ResolveProperty(struct bc_Class* classz, bc_StringView name,
                                int* outIndex);
#endif