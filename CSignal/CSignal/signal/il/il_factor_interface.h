#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_INTERFACE_H
#define SIGNAL_IL_IL_FACTOR_INTERFACE_H
#include "../vm/enviroment.h"
#include "il_ehandler.h"
//#include "../vm/opcode.h"
//#include "../vm/opcode_buf.h"
//struct opcode_buf;

/**
 * 計算可能な要素の種類.
 */
typedef enum il_factor_type {
	ilfactor_int,
	ilfactor_double,
	ilfactor_cquote,
	ilfactor_squote,
	ilfactor_unary_op,
	ilfactor_binary_op,
	ilfactor_call,
	ilfactor_invoke,
	ilfactor_named_invoke,
	ilfactor_variable,
	ilfactor_this,
	ilfactor_super,
	ilfactor_new_instance,
	ilfactor_field_access,
	ilfactor_static_field_access,
} il_factor_type;

//ファクターとして扱える要素自身が内側にファクターを含む(再帰)
//ために、スーパーセットの定義ではサブセットを前方宣言します。
//サブセットはこのファイルをインクルードして、
//il_factor で計算可能な要素を抽象的に扱えます。
//例えば、関数の実行には計算可能な実引数が必要ですが、
//関数自体が計算可能な要素です。
//ここでは関数呼び出しを前方宣言し、
//関数呼び出しを表す構造体では実引数の一覧を il_factor型で定義します。
//詳細は il_factor_impl.h を参照してください。
struct il_factor_int;
struct il_factor_double;
struct il_factor_char;
struct il_factor_string;
struct il_factor_call;
struct il_factor_invoke;
struct il_factor_named_invoke;
struct il_factor_variable;
struct il_factor_unary_op;
struct il_factor_binary_op;
struct il_factor_this;
struct il_factor_super;
struct il_factor_new_instance;
struct il_factor_field_access;
struct il_factor_static_field_access;

/**
 * 計算可能な要素.
 */
typedef struct il_factor {
	il_factor_type type;
	union {
		struct il_factor_int* int_;
		struct il_factor_double* double_;
		struct il_factor_char* char_;
		struct il_factor_string* string_;
		struct il_factor_call* call_;
		struct il_factor_invoke* invoke_;
		struct il_factor_named_invoke* named_invoke_;
		struct il_factor_variable* variable_;
		struct il_factor_unary_op* unary_;
		struct il_factor_binary_op* binary_;
		struct il_factor_this* this_;
		struct il_factor_super* super_;
		struct il_factor_new_instance* new_instance_;
		struct il_factor_field_access* field_access_;
		struct il_factor_static_field_access* static_field_access;
	} u;
} il_factor;

/**
 * 計算可能な要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_dump(il_factor* self, int depth);

/**
 * オペコードを生成します.
 * @param self
 * @param env
 */
void il_factor_generate(il_factor* self, enviroment* env);

/**
 * 因子を読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_factor_load(il_factor* self, enviroment* env, il_ehandler* eh);

/**
 * この因子が表す型を返します.
 * @param self
 * @param env
 * @return
 */
struct type* il_factor_eval(il_factor* self, enviroment* env);

/**
 * 計算可能な要素を開放します.
 * @param self
 */
void il_factor_delete(il_factor* self);
#endif // !SIGNAL_IL_IL_FACTOR_INTERFACE_H
