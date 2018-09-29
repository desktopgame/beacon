#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"

struct method;
struct constructor;
struct operator_overload;
struct generic_type;

typedef enum call_frame_tag {
	FRAME_RESOLVE_T,
	FRAME_SELF_INVOKE_T,
	FRAME_STATIC_INVOKE_T,
	FRAME_INSTANCE_INVOKE_T,
} call_frame_tag;

typedef struct call_resolve {
	struct generic_type* gtype;
	Vector* typeargs;
} call_resolve;

typedef struct call_self_invoke {
	Vector* args;
	Vector* typeargs;
} call_self_invoke;

typedef struct call_static_invoke {
	Vector* args;
	Vector* typeargs;
} call_static_invoke;

typedef struct call_instance_invoke {
	struct generic_type* receiver;
	Vector* args;
	Vector* typeargs;
} call_instance_invoke;

typedef struct call_frame {
	call_frame_tag tag;
	union {
		call_resolve resolve;
		call_self_invoke self_invoke;
		call_static_invoke static_invoke;
		call_instance_invoke instance_invoke;
	} u;
} call_frame;

#define call_NewFrame(tag) (call_frame_malloc(tag, __FILE__, __LINE__))
call_frame* call_frame_malloc(call_frame_tag tag, const char* filename, int lineno);

void call_DeleteFrame(call_frame* self);
#endif