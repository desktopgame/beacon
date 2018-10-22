#ifndef BEACON_IL_CALL_FRAME_H
#define BEACON_IL_CALL_FRAME_H
#include "../util/vector.h"

struct method;
struct constructor;
struct operator_overload;
struct generic_type;

typedef enum CallFrameTag {
	FRAME_RESOLVE_T,
	FRAME_SELF_INVOKE_T,
	FRAME_STATIC_INVOKE_T,
	FRAME_INSTANCE_INVOKE_T,
} CallFrameTag;

typedef struct CallResolve {
	struct generic_type* GType;
	Vector* TypeArgs;
} CallResolve;

typedef struct CallSelfInvoke {
	Vector* Args;
	Vector* TypeArgs;
} CallSelfInvoke;

typedef struct CallStaticInvoke {
	Vector* Args;
	Vector* TypeArgs;
} CallStaticInvoke;

typedef struct CallInstanceInvoke {
	struct generic_type* Receiver;
	Vector* Args;
	Vector* TypeArgs;
} CallInstanceInvoke;

typedef struct CallFrame {
	CallFrameTag Tag;
	union {
		CallResolve Resolve;
		CallSelfInvoke SelfInvoke;
		CallStaticInvoke StaticInvoke;
		CallInstanceInvoke InstanceInvoke;
	} Kind;
} CallFrame;

#define NewCallFrame(tag) (MallocCallFrame(tag, __FILE__, __LINE__))
CallFrame* MallocCallFrame(CallFrameTag tag, const char* filename, int lineno);

void DeleteCallFrame(CallFrame* self);
#endif