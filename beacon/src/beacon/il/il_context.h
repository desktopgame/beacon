#pragma once
#ifndef BEACON_IL_il_context_H
#define BEACON_IL_il_context_H
#include "../util/vector.h"
#include <stdbool.h>

/**
 * ILを読み込むためのキャッシュです.
 */
typedef struct il_context {
	vector* namespace_vec;
	vector* type_vec;
	vector* method_vec;
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
	vector* eval_ctor_vec;
	bool toplevel;
} il_context;

struct namespace_;
struct class_;
struct fqcn_cache;

/**
 * ILキャッシュを作成します.
 * @return
 */
il_context* il_context_new();

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
