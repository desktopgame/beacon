#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_INTERFACE_H
#define SIGNAL_IL_IL_FACTOR_INTERFACE_H
/**
 * 計算可能な要素の種類.
 */
typedef enum il_factor_type {
	factor_int,
	factor_double,
	factor_cquote,
	factor_squote,
	factor_unary_op,
	factor_binary_op,
	factor_call,
	factor_invoke,
	factor_variable,
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
struct il_factor_variable;

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
		struct il_factor_variable* variable_;
	} u;
} il_factor;

/**
 * 計算可能な要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_dump(il_factor* self, int depth);

/**
 * 計算可能な要素を開放します.
 * @param self
 */
void il_factor_delete(il_factor* self);
#endif // !SIGNAL_IL_IL_FACTOR_INTERFACE_H
