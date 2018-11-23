#ifndef BEACON_ENV_COROUTINE_H
#define BEACON_ENV_COROUTINE_H
#include "../vm/yield_context.h"
#include "object.h"

typedef struct bc_Coroutine {
        bc_Object Super;
        bc_YieldContext* Context;
} bc_Coroutine;
#endif