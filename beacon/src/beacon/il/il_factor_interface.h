#pragma once
#ifndef BEACON_IL_IL_FACTOR_INTERFACE_H
#define BEACON_IL_IL_FACTOR_INTERFACE_H
#include "../vm/enviroment.h"
#include "il_context.h"
#include "il_error.h"
#include <stdint.h>
#include <assert.h>
#include "../env/generic_type.h"
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
	ilfactor_variable,
	ilfactor_this,
	ilfactor_super,
	ilfactor_new_instance,
	ilfactor_cast,
	ilfactor_bool,
	ilfactor_null,
	ilfactor_as,
	ilfactor_inc,
	ilfactor_dec,
	ilfactor_call_op,
	ilfactor_member_op
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
struct il_factor_variable;
struct il_factor_unary_op;
struct il_factor_binary_op;
struct il_factor_this;
struct il_factor_super;
struct il_factor_new_instance;
struct il_factor_cast;
struct il_factor_bool;
struct il_factor_null;
struct il_factor_as;
struct il_factor_inc;
struct il_factor_dec;
struct il_factor_call_op;
struct il_factor_member_op;

/**
 * 計算可能な要素.
 */
typedef struct il_factor {
	il_factor_type type;
	uint32_t lineno;
	union {
		struct il_factor_int* int_;
		struct il_factor_double* double_;
		struct il_factor_char* char_;
		struct il_factor_string* string_;
		struct il_factor_variable* variable_;
		struct il_factor_unary_op* unary_;
		struct il_factor_binary_op* binary_;
		struct il_factor_this* this_;
		struct il_factor_super* super_;
		struct il_factor_new_instance* new_instance_;
		struct il_factor_cast* cast_;
		struct il_factor_bool* bool_;
		struct il_factor_null* null_;
		struct il_factor_as* as_;
		struct il_factor_inc* inc_;
		struct il_factor_dec* dec_;
		struct il_factor_call_op* call_;
		struct il_factor_member_op* member_;
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
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cache
 */
void il_factor_generate(il_factor* self, enviroment* env, il_context* ilctx);

/**
 * 因子を読み込みます.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_load(il_factor* self, enviroment* env, il_context* ilctx);

/**
 * この因子が表す型を返します.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_eval(il_factor* self, enviroment* env, il_context* ilctx);

/**
 * 計算可能な要素を開放します.
 * @param self
 */
void il_factor_delete(il_factor* self);
#endif // !SIGNAL_IL_IL_FACTOR_INTERFACE_H
