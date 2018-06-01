#ifndef BEACON_VM_DEFER_CONTEXT_H
#define BEACON_VM_DEFER_CONTEXT_H
#include "label.h"
#include "../util/vector.h"
typedef struct defer_context {
	label* offset;
	vector* bind;
} defer_context;

defer_context* defer_context_new();

void defer_context_delete(defer_context* self);
#endif