#pragma once
#ifndef SIGNAL_ENV_OBJECT_H
#define SIGNAL_ENV_OBJECT_H
#include "../util/vector.h"
#include <stdbool.h>

struct type;
struct vtable;
/** 
 * オブジェクトの着色状態.
 * インクリメンタルGCのためのフラグです。
 */
typedef enum object_paint {
	paint_unmarked,
	paint_marked
//	paint_white,
//	paint_black,
//	paint_gray
} object_paint ;

/**
 * オブジェクトの種類を表す列挙.
 */
typedef enum object_tag {
	object_int,
	object_double,
	object_char,
	object_string,
	object_bool,
	object_ref,
} object_tag;

/**
 * ヒープに関連付けされるオブジェクト.
 * signal で使用される全てのデータはこれ。
 */
typedef struct object {
	struct type* type;
	//-初期化時
	//-宣言時と互換性のある
	//異なる型が代入されたとき
	//この vptr を入れ替える
	struct vtable* vptr;
	object_paint paint;
	object_tag tag;
	vector* nativeSlotVec;
	union {
		int int_;
		double double_;
		char char_;
		char* string_;
		bool bool_;
		vector* field_vec;
	} u;
} object;

/**
 * 整数型のオブジェクトを作成します.
 * @param i
 * @return
 */
object* object_int_new(int i);

/**
 * 浮動小数型のオブジェクトを作成します.
 * @param d
 * @return
 */
object* object_double_new(double d);

/**
 * 文字型のオブジェクトを作成します.
 * @param c
 * @return
 */
object* object_char_new(char c);

/**
 * 文字列型のオブジェクトを作成します.
 * @param s
 * @return
 */
object* object_string_new(const char* s);

/**
 * 真偽値型のオブジェクトを作成します.
 * @param b
 * @return
 */
object* object_bool_new(bool b);

/**
 * 参照型のオブジェクトを作成します.
 * @return
 */
object* object_ref_new();

/**
 * 真偽値型の値を参照します.
 * @param b
 * @return
 */
object* object_bool_get(bool b);

/**
 * trueを参照します.
 * @return
 */
object* object_true();

/**
 * falseを参照します.
 * @return
 */
object* object_false();

/**
 * オブジェクトとフィールドを開放します.
 * @param self
 */
void object_delete(object* self);
#endif // !SIGNAL_ENV_OBJECT_H
