#ifndef BEACON_ENV_TYPE_RESOLVE_H
#define BEACON_ENV_TYPE_RESOLVE_H
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "../generic_type.h"
#include "../type_impl.h"

typedef enum bc_SearchOption {
        MATCH_ALL,
        MATCH_PUBLIC_ONLY,
        MATCH_PUBLIC_OR_PROTECTED
} bc_SearchOption;

bc_Method* bc_FindMethod(bc_Vector* methods, bc_StringView name,
                         bc_Vector* args, bc_Vector* type_args,
                         bc_ExecutePhase phase, bc_SearchOption option,
                         int* outIndex);
#endif