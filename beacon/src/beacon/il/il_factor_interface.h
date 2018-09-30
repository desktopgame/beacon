#pragma once
#ifndef BEACON_IL_IL_FACTOR_INTERFACE_H
#define BEACON_IL_IL_FACTOR_INTERFACE_H
#include "../vm/enviroment.h"
#include "../util/string_buffer.h"
#include "../error.h"
#include "call_context.h"
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
	ILFACTOR_INT_T,
	ILFACTOR_DOUBLE_T,
	ILFACTOR_CHAR_T,
	ILFACTOR_STRING_T,
	ILFACTOR_UNARY_OP_T,
	ILFACTOR_BINARY_OP_T,
	ILFACTOR_ASSIGN_T,
	ILFACTOR_VARIABLE_T,
	ILFACTOR_THIS_T,
	ILFACTOR_SUPER_T,
	ILFACTOR_NEW_INSTANCE_T,
	ILFACTOR_BOOL_T,
	ILFACTOR_NULL_T,
	ILFACTOR_AS_T,
	ILFACTOR_CALL_OP_T,
	ILFACTOR_MEMBER_OP_T,
	ILFACTOR_INSTANCEOF_T,
	ILFACTOR_EXPLICIT_BINARY_OP_T,
	ILFACTOR_EXPLICIT_UNARY_OP_T,
	ILFACTOR_PROPERTY_T,
	ILFACTOR_SUBSCRIPT_T
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
struct il_factor_assign_op;
struct il_factor_this;
struct il_factor_super;
struct il_factor_new_instance;
struct il_factor_bool;
struct il_factor_null;
struct il_factor_as;
struct il_factor_inc;
struct il_factor_dec;
struct il_factor_call_op;
struct il_factor_member_op;
struct il_factor_instanceof;
struct il_factor_explicit_binary_op;
struct il_factor_explicit_unary_op;
struct il_factor_property;
struct il_factor_subscript;

/**
 * 計算可能な要素.
 */
typedef struct il_factor {
	il_factor_type type;
	int lineno;
	union {
		struct il_factor_int* int_;
		struct il_factor_double* double_;
		struct il_factor_char* char_;
		struct il_factor_string* string_;
		struct il_factor_variable* variable_;
		struct il_factor_unary_op* unary_;
		struct il_factor_assign_op* assign_;
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
		struct il_factor_instanceof* instanceof_;
		struct il_factor_explicit_binary_op* exp_binary_op;
		struct il_factor_explicit_unary_op* exp_unary_op;
		struct il_factor_property* prop;
		struct il_factor_subscript* subscript;
	} u;
} il_factor;

#define il_factor_new(type) (MallocILFactor(type, __FILE__, __LINE__))
il_factor* MallocILFactor(il_factor_type type, const char* filename, int lineno);

/**
 * オペコードを生成します.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILFactor(il_factor* self, enviroment* env, call_context* cctx);

/**
 * 因子を読み込みます.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 */
void LoadILFactor(il_factor* self, enviroment* env, call_context* cctx);

/**
 * この因子が表す型を返します.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 * @return
 */
generic_type* EvalILFactor(il_factor* self, enviroment* env, call_context* cctx);

/**
 * ファクターの文字列表現を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
char* ILFactorToString(il_factor* self, enviroment* env);

/**
 * @param sb
 * @param args
 */
void ILArgsToString(string_buffer* sb, Vector* args, struct enviroment* env);

/**
 * @param sb
 * @param type_args
 */
void ILTypeArgsToString(string_buffer* sb, Vector* type_args, struct enviroment* env);

/**
 * 計算可能な要素を開放します.
 * @param self
 */
void DeleteILFactor(il_factor* self);
#endif // !SIGNAL_IL_IL_FACTOR_INTERFACE_H
