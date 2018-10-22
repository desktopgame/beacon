#ifndef BEACON_IL_CALL_CONTEXT_H
#define BEACON_IL_CALL_CONTEXT_H
#include "../util/vector.h"
#include "call_frame.h"
#include "control_structure.h"
struct namespace_;
struct type;
struct class_;
struct method;
struct constructor;
struct operator_overload;
struct generic_type;
struct fqcn_cache;

typedef enum CallContextTag {
	//プログラムのトップレベル
	CALL_TOP_T,
	//メソッド
	CALL_METHOD_T,
	//コンストラクタ
	CALL_CTOR_T,
	//演算子オーバーロード
	CALL_OPOV_T,
	//コンストラクタの連鎖
	CALL_CTOR_ARGS_T,

	CALL_DECL_T
} CallContextTag;

typedef struct CallContext {
	Vector* call_stack;
	ControlStructure control;
	CallContextTag tag;
	struct namespace_* scope;
	struct type* ty;
	union {
		struct method* mt;
		struct constructor* ctor;
		struct operator_overload* opov;
	} u;
} CallContext;

#define NewCallContext(tag) (MallocCContext(tag, __FILE__, __LINE__))
CallContext* MallocCContext(CallFrameTag tag, const char* filename, int lineno);

#define PushCallContext(self, tag) (PushImplCallContext(self, tag, __FILE__, __LINE__))
CallFrame* PushImplCallContext(CallContext* self, CallFrameTag tag, const char* filename, int lineno);

CallFrame* TopCallContext(CallContext* self);

void PopCallContext(CallContext* self);

struct namespace_* GetNamespaceCContext(CallContext* self);

struct method* GetMethodCContext(CallContext* self);

struct type* GetTypeCContext(CallContext* self);

struct class_* GetClassCContext(CallContext* self);

struct generic_type* GetReceiverCContext(CallContext* self);

struct type* GetEvalTypeCContext(CallContext* self, struct fqcn_cache* fqcn);

Vector* GetTypeArgsCContext(CallContext* self);

bool IsStaticCContext(CallContext* self);

void DeleteCallContext(CallContext* self);
#endif