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

typedef enum call_context_tag {
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
} call_context_tag;

typedef struct call_context {
	Vector* call_stack;
	ControlStructure control;
	call_context_tag tag;
	struct namespace_* scope;
	struct type* ty;
	union {
		struct method* mt;
		struct constructor* ctor;
		struct operator_overload* opov;
	} u;
} call_context;

#define NewCallContext(tag) (MallocCContext(tag, __FILE__, __LINE__))
call_context* MallocCContext(CallFrameTag tag, const char* filename, int lineno);

#define PushCallContext(self, tag) (PushImplCallContext(self, tag, __FILE__, __LINE__))
call_frame* PushImplCallContext(call_context* self, CallFrameTag tag, const char* filename, int lineno);

call_frame* TopCallContext(call_context* self);

void PopCallContext(call_context* self);

struct namespace_* GetNamespaceCContext(call_context* self);

struct method* GetMethodCContext(call_context* self);

struct type* GetTypeCContext(call_context* self);

struct class_* GetClassCContext(call_context* self);

struct generic_type* GetReceiverCContext(call_context* self);

struct type* GetEvalTypeCContext(call_context* self, struct fqcn_cache* fqcn);

Vector* GetTypeArgsCContext(call_context* self);

bool IsStaticCContext(call_context* self);

void DeleteCallContext(call_context* self);
#endif