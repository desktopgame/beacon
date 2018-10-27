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
typedef enum ILFactorType {
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
} ILFactorType;

//ファクターとして扱える要素自身が内側にファクターを含む(再帰)
//ために、スーパーセットの定義ではサブセットを前方宣言します。
//サブセットはこのファイルをインクルードして、
//ILFactor で計算可能な要素を抽象的に扱えます。
//例えば、関数の実行には計算可能な実引数が必要ですが、
//関数自体が計算可能な要素です。
//ここでは関数呼び出しを前方宣言し、
//関数呼び出しを表す構造体では実引数の一覧を ILFactor型で定義します。
//詳細は il_factor_impl.h を参照してください。
struct ILInt;
struct ILDouble;
struct ILChar;
struct ILString;
struct ILFactor_variable;
struct ILFactor_unary_op;
struct ILBinaryOp;
struct ILAssignOp;
struct ILThis;
struct ILSuper;
struct ILFactor_new_instance;
struct ILBool;
struct ILFactor_null;
struct ILAs;
struct ILFactor_inc;
struct ILFactor_dec;
struct ILFactor_call_op;
struct ILFactor_member_op;
struct ILFactor_instanceof;
struct ILFactor_explicit_binary_op;
struct ILFactor_explicit_unary_op;
struct ILFactor_Property;
struct ILFactor_subscript;

/**
 * 計算可能な要素.
 */
typedef struct ILFactor {
	ILFactorType type;
	int lineno;
	union {
		struct ILInt* int_;
		struct ILDouble* double_;
		struct ILChar* char_;
		struct ILString* string_;
		struct ILFactor_variable* variable_;
		struct ILFactor_unary_op* unary_;
		struct ILAssignOp* assign_;
		struct ILBinaryOp* binary_;
		struct ILThis* this_;
		struct ILSuper* super_;
		struct ILFactor_new_instance* new_instance_;
		struct ILFactor_cAST* cast_;
		struct ILBool* bool_;
		struct ILFactor_null* null_;
		struct ILAs* as_;
		struct ILFactor_inc* inc_;
		struct ILFactor_dec* dec_;
		struct ILFactor_call_op* call_;
		struct ILFactor_member_op* member_;
		struct ILFactor_instanceof* instanceof_;
		struct ILFactor_explicit_binary_op* exp_binary_op;
		struct ILFactor_explicit_unary_op* exp_unary_op;
		struct ILFactor_Property* prop;
		struct ILFactor_subscript* subscript;
	} u;
} ILFactor;

#define ILFactor_new(type) (MallocILFactor(type, __FILE__, __LINE__))
ILFactor* MallocILFactor(ILFactorType type, const char* filename, int lineno);

/**
 * オペコードを生成します.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILFactor(ILFactor* self, Enviroment* env, CallContext* cctx);

/**
 * 因子を読み込みます.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 */
void LoadILFactor(ILFactor* self, Enviroment* env, CallContext* cctx);

/**
 * この因子が表す型を返します.
 * この関数は ILパニック を発生させることがあります。
 * @param self
 * @param env
 * @param cctx
 * @return
 */
GenericType* EvalILFactor(ILFactor* self, Enviroment* env, CallContext* cctx);

/**
 * ファクターの文字列表現を返します.
 * @param self
 * @param env
 * @param ilctx
 * @return
 */
char* ILFactorToString(ILFactor* self, Enviroment* env);

/**
 * @param sb
 * @param args
 */
void ILArgsToString(Buffer* sb, Vector* args, Enviroment* env);

/**
 * @param sb
 * @param type_args
 */
void ILTypeArgsToString(Buffer* sb, Vector* type_args, Enviroment* env);

/**
 * 計算可能な要素を開放します.
 * @param self
 */
void DeleteILFactor(ILFactor* self);
#endif // !SIGNAL_IL_IL_FACTOR_INTERFACE_H
