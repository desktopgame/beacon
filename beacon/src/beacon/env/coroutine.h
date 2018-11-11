#ifndef BEACON_ENV_COROUTINE_H
#define BEACON_ENV_COROUTINE_H
#include "object.h"
#include "../vm/yield_context.h"

typedef struct Coroutine {
	Object Super;
	YieldContext* Context;
} Coroutine;
#endif