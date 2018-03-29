#pragma once
#ifndef BEACON_ENV_OBJECT_H
#define BEACON_ENV_OBJECT_H
#include "../util/vector.h"
#include <stdbool.h>

struct generic_type;
struct vtable;
/** 
 * オブジェクトの着色状態.
 * インクリメンタルGCのためのフラグです。
 */
typedef enum object_paint {
	paint_unmarked,
	paint_marked,
	//コンテキストが終了するまで
	//GCの対象にならない
	//ソースコード中に直接記述されたリテラルのためのフラグ。
	paint_onexit,
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
	object_null,
} object_tag;

/**
 * ヒープに関連付けされるオブジェクト.
 * signal で使用される全てのデータはこれ。
 */
typedef struct object {
	struct generic_type* gtype;
	//-初期化時
	//-宣言時と互換性のある
	//異なる型が代入されたとき
	//この vptr を入れ替える
	struct vtable* vptr;
	object_paint paint;
	object_tag tag;
	vector* native_slot_vec;
	union {
		int int_;
		double double_;
		char char_;
//		char* string_;
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
object* object_get_true();

/**
 * falseを参照します.
 * @return
 */
object* object_get_false();

/**
 * nullを参照します.
 * @return
 */
object* object_get_null();

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を +1 します.
 * @param self
 */
void object_inc(object* self);

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を -1 します.
 * @param self
 */
void object_dec(object* self);

/**
 * このオブジェクトを複製します.
 * int/double/char/boolでのみ使用可能です。
 * @param self
 * @return
 */
object* object_copy(object* self);
/**
 * このオブジェクトを複製します.
 * int/double/char/boolでのみ使用可能です。
 * @param self
 * @return
 */
object* object_copy_s(object* self);

/**
 * このオブジェクトと
 * このオブジェクトから参照可能なオブジェクトを全てマークします.
 * @param self
 */
void object_markall(object* self);

/**
 * まだ開放されていないオブジェクトの数を返します.
 * @return
 */
int object_count();

/**
 * オブジェクトの詳細を出力します.
 * @param self
 */
void object_print(object* self);

/**
 * オブジェクトを開放します.
 * @param self
 */
void object_delete(object* self);
#endif // !SIGNAL_ENV_OBJECT_H
