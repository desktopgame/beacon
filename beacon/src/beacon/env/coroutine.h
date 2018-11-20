#ifndef BEACON_ENV_COROUTINE_H
#define BEACON_ENV_COROUTINE_H
#include "object.h"
#include "../vm/yield_context.h"

typedef struct bc_Coroutine {
	bc_Object Super;
	bc_YieldContext* Context;
} bc_Coroutine;
#endif