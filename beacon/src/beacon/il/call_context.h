#ifndef BEACON_IL_CALL_CONTEXT_H
#define BEACON_IL_CALL_CONTEXT_H
#include "../util/vector.h"
#include "call_frame.h"

typedef struct call_context {
	vector* call_stack;
} call_context;

#define call_context_new() (call_context_malloc(__FILE__, __LINE__))
call_context* call_context_malloc(const char* filename, int lineno);

call_frame* call_context_push(call_context* self, call_frame_tag tag);

call_frame* call_context_top(call_context* self);

void call_context_pop(call_context* self);

void call_context_delete(call_context* self);
#endif