#pragma once
#ifndef BEACON_ENV_OBJECT_H
#define BEACON_ENV_OBJECT_H
#include "../util/vector.h"
#include <stdbool.h>

#define OBJ2INT(a) (object_obj2int(a))
#define OBJ2DOUBLE(a) (object_obj2double(a))
#define OBJ2BOOL(a) (object_obj2bool(a))
#define OBJ2CHAR(a) (object_obj2char(a))

#define INT2OBJ(a) (object_int2obj(a))
#define DOUBLE2OBJ(a) (object_double2obj(a))
#define BOOL2OBJ(a) (object_bool2obj(a))
#define CHAR2OBJ(a) (object_char2obj(a))

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
	object_array,
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
#define object_int_new(i) (object_int_malloc(i, __FILE__, __LINE__))
object* object_int_malloc(int i, const char* filename, int lineno);

/**
 * 浮動小数型のオブジェクトを作成します.
 * @param d
 * @return
 */
#define object_double_new(d) (object_double_malloc(d, __FILE__, __LINE__))
object* object_double_malloc(double d, const char* filename, int lineno);

/**
 * 文字型のオブジェクトを作成します.
 * @param c
 * @return
 */
#define object_char_new(c) (object_char_malloc(c, __FILE__, __LINE__))
object* object_char_malloc(char c, const char* filename, int lineno);

/**
 * 文字列型のオブジェクトを作成します.
 * @param s
 * @return
 */
#define object_string_new(s) (object_string_malloc(s, __FILE__, __LINE__))
object* object_string_malloc(const char* s, const char* filename, int lineno);

/**
 * 参照型のオブジェクトを作成します.
 * @return
 */
#define object_ref_new() (object_ref_malloc(__FILE__, __LINE__))
object* object_ref_malloc(const char* filename, int lineno);

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
 * @param paint
 */
void object_paintall(object* self, object_paint paint);

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

/**
 * beaconからCの int へ変換します.
 * @param self
 * @return
 */
int object_obj2int(object* self);

/**
 * beaconからCの double へ変換します.
 * @param self
 * @return
 */
double object_obj2double(object* self);

/**
 * beaconからCの bool へ変換します.
 * @param self
 * @return
 */
bool object_obj2bool(object* self);

/**
 * beaconからCの char へ変換します.
 * @param self
 * @return
 */
char object_obj2char(object* self);

/**
 * Cからbeaconの Int へ変換します.
 * @param i
 * @return
 */
object* object_int2obj(int i);

/**
 * Cからbeaconの Double へ変換します.
 * @param d
 * @return
 */
object* object_double2obj(double d);

/**
 * Cからbeaconの bool へ変換します.
 * @param b
 * @return
 */
object* object_bool2obj(bool b);

/**
 * Cからbeaconの char へ変換します.
 * @param c
 * @return
 */
object* object_char2obj(char c);
#endif // !SIGNAL_ENV_OBJECT_H
