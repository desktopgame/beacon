#ifndef BEACON_ENV_TYPE_RESOLVE_H
#define BEACON_ENV_TYPE_RESOLVE_H
#include "../../util/string_pool.h"
#include "../../util/vector.h"
#include "../generic_type.h"
#include "../type_impl.h"

bc_Method* bc_resolve_FindMethod(bc_Vector* methods, bc_StringView name,
                                 bc_Vector* args, bc_Vector* type_args,
                                 bc_ExecutePhase phase);
#endif