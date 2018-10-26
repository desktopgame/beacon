#ifndef BEACON_IL_CALL_CONTEXT_H
#define BEACON_IL_CALL_CONTEXT_H
#include "../util/vector.h"
#include "call_frame.h"
#include "control_structure.h"
struct Namespace;
struct type;
struct class_;
struct Method;
struct Constructor;
struct OperatorOverload;
struct GenericType;
struct FQCNCache;

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
	Vector* CallStack;
	ControlStructure Control;
	CallContextTag Tag;
	struct Namespace* Scope;
	struct type* Ty;
	union {
		struct Method* Method;
		struct Constructor* Ctor;
		struct OperatorOverload* OpOv;
	} Kind;
} CallContext;

#define NewCallContext(tag) (MallocCContext(tag, __FILE__, __LINE__))
CallContext* MallocCContext(CallFrameTag tag, const char* filename, int lineno);

#define PushCallContext(self, tag) (PushImplCallContext(self, tag, __FILE__, __LINE__))
CallFrame* PushImplCallContext(CallContext* self, CallFrameTag tag, const char* filename, int lineno);

CallFrame* TopCallContext(CallContext* self);

void PopCallContext(CallContext* self);

struct Namespace* GetNamespaceCContext(CallContext* self);

struct Method* GetMethodCContext(CallContext* self);

struct type* GetTypeCContext(CallContext* self);

struct class_* GetClassCContext(CallContext* self);

struct GenericType* GetReceiverCContext(CallContext* self);

struct type* GetEvalTypeCContext(CallContext* self, struct FQCNCache* fqcn);

Vector* GetTypeArgsCContext(CallContext* self);

bool IsStaticCContext(CallContext* self);

void DeleteCallContext(CallContext* self);
#endif