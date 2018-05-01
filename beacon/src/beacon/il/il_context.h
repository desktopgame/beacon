#pragma once
#ifndef BEACON_IL_il_context_H
#define BEACON_IL_il_context_H
#include "../util/vector.h"
#include <stdbool.h>
struct class_loader;

#define ILCTX_PUSH_NAMESPACE(ctx, a) vector_push(ctx->namespace_vec, a)
#define ILCTX_PUSH_TYPE(ctx, a) vector_push(ctx->type_vec, a)
#define ILCTX_PUSH_METHOD(ctx, a) vector_push(ctx->method_vec, a)
#define ILCTX_PUSH_CTOR(ctx, a) vector_push(ctx->ctor_vec, a)
#define ILCTX_PUSH_RECEIVER(ctx, a) vector_push(ctx->receiver_vec, a)
#define ILCTX_PUSH_TYPE_ARGS(ctx, a) vector_push(ctx->type_args_vec, a)

#define ILCTX_NAMESPACE(ctx) ((namespace_*)vector_top(ctx->namespace_vec))
#define ILCTX_TYPE(ctx) ((type*)vector_top(ctx->type_vec))
#define ILCTX_METHOD(ctx) ((method*)vector_top(ctx->method_vec))
#define ILCTX_CTOR(ctx) ((constructor*)vector_top(ctx->ctor_vec))
#define ILCTX_RECEIVER(ctx) ((generic_type*)vector_top(ctx->receiver_vec))
#define ILCTX_TYPE_ARGS(ctx) ((vector*)vector_top(ctx->type_args_vec))

#define ILCTX_POP_NAMESPACE(ctx) vector_pop(ctx->namespace_vec)
#define ILCTX_POP_TYPE(ctx) vector_pop(ctx->type_vec)
#define ILCTX_POP_METHOD(ctx) vector_pop(ctx->method_vec)
#define ILCTX_POP_CTOR(ctx) vector_pop(ctx->ctor_vec)
#define ILCTX_POP_RECEIVER(ctx) vector_pop(ctx->receiver_vec)
#define ILCTX_POP_TYPE_ARGS(ctx) vector_pop(ctx->type_args_vec)

/**
 * ILを読み込むためのキャッシュです.
 */
typedef struct il_context {
	vector* namespace_vec;
	vector* type_vec;
	vector* method_vec;
	vector* ctor_vec;
	vector* receiver_vec;
	vector* type_args_vec;
	vector* while_start_vec;
	vector* while_end_vec;
	//メソッドの探索とコンストラクタの探索は
	//部分的には似ていますが、
	//コンストラクタはレシーバがいないのにインスタンスメソッドのように
	//クラスに定義された型変数を使用できるという点で特殊です。
	//パラメータが T であり、インスタンスメソッドであるなら
	//それを実行する実体化されたレシーバから型を取り出せますが、
	//(つまり、receiver_vecの先頭を参照する)
	//コンストラクタの場合ではnew演算子から参照する必要があります。
	bool toplevel;
	int find_instance;
	int find_static;
	struct class_loader* class_loader_ref;
} il_context;

struct namespace_;
struct class_;
struct fqcn_cache;

/**
 * ILキャッシュを作成します.
 * @param class_loader_ref
 * @return
 */
il_context* il_context_new(struct class_loader* class_loader_ref);

/**
 * 現在のスコープの名前空間を返します.
 * @param self
 * @return
 */
struct namespace_* il_context_namespace(il_context* self);

/**
 * 現在解析中のクラスを返します.
 * @param self
 * @return
 */
struct class_* il_context_class(il_context* self, struct fqcn_cache* fqcn);

/**
 * ILキャッシュを開放します
 * @param self
 */
void il_context_delete(il_context* self);
#endif // !SIGNAL_IL_il_context_H
