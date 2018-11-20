//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file enviroment.h
 * @brief beaconインタプリタの実行に必要な環境を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_VM_ENVIROMENT_H
#define BEACON_VM_ENVIROMENT_H
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "opcode_buf.h"
#include "symbol_table.h"
#include <stdbool.h>
struct bc_Class;
struct bc_Object;
struct bc_ClassLoader;
struct bc_FQCNCache;
/**
 * プログラムの実行環境です.
 * スタックや変数は実行時に変化しますが、
 * 定数プールやオペランドのようなコンパイル時に決定して
 * 不変なものをここでは Enviroment と呼称します。
 */
typedef struct bc_Enviroment {
	struct bc_ClassLoader* ContextRef;
	bc_OpcodeBuf* Bytecode;
	bc_SymbolTable* Symboles;
	Vector* ConstantPool;
	Vector* LineRangeTable;
} bc_Enviroment;

/**
 * 環境を生成します.
 * @return
 */
bc_Enviroment* bc_NewEnviroment();

/**
 * 指定の行番号を開始します.
 * @param self
 * @param lineno
 */
void bc_AddRangeEnviroment(bc_Enviroment* self, int lineno);

/**
 * この Enviroment に含まれるオペコードの一覧をダンプします.
 * DumpOpcodeBuf との違いは、行番号を出力できる点です。
 * @param self
 * @param depth
 */
void bc_DumpEnviromentOp(bc_Enviroment* self, int depth);

/**
 * 定数プールに整数を追加して、その位置を返します.
 * @param i
 * @return
 */
int bc_AddCIntEnviroment(bc_Enviroment* self, int i);

/**
 * 定数プールに浮動小数を追加して、その位置を返します.
 * @param d
 * @return
 */
int bc_AddCDoubleEnviroment(bc_Enviroment* self, double d);

/**
 * 定数プールに文字を追加して、その位置を返します.
 * @param c
 * @return
 */
int bc_AddCCharEnviroment(bc_Enviroment* self, char c);

/**
 * 定数プールに文字列を追加して、その位置を返します.
 * @param sv
 * @return
 */
int bc_AddCStringEnviroment(bc_Enviroment* self, StringView sv);

/**
 * 指定位置のオペコード/オペランドを返します.
 * @param self
 * @param index
 * @return
 */
VectorItem bc_GetEnviromentSourceAt(bc_Enviroment* self, int index);

/**
 * 指定位置の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_Object* bc_GetEnviromentConstantAt(bc_Enviroment* self, int index);

/**
 * 指定位置の整数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_Object* bc_GetEnviromentCIntAt(bc_Enviroment* self, int index);

/**
 * 指定位置の浮動小数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_Object* bc_GetEnviromentCDoubleAt(bc_Enviroment* self, int index);

/**
 * 指定位置の文字型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_Object* bc_GetEnviromentCCharAt(bc_Enviroment* self, int index);

/**
 * 指定位置の文字列型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_Object* bc_GetEnviromentCStringAt(bc_Enviroment* self, int index);

/**
 * 環境を開放します.
 * @return
 */
void bc_DeleteEnviroment(bc_Enviroment* self);
#endif // !SIGNAL_VM_ENVIROMENT_H
