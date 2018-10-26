#pragma once
#ifndef BEACON_ENV_OBJECT_H
#define BEACON_ENV_OBJECT_H
#include "../util/vector.h"
#include <stdbool.h>

#define OBJ2INT(a) (ObjectToInt(a))
#define OBJ2DOUBLE(a) (ObjectToDouble(a))
#define OBJ2BOOL(a) (ObjectToBool(a))
#define OBJ2CHAR(a) (ObjectToChar(a))
#define OBJ2LONG(a) (ObjectToLong(a))

#define INT2OBJ(a) (IntToObject(a))
#define DOUBLE2OBJ(a) (DoubleToObject(a))
#define BOOL2OBJ(a) (BoolToObject(a))
#define CHAR2OBJ(a) (CharToObject(a))
#define LONG2OBJ(a) (LongToObject(a))

struct generic_type;
struct VTable;
/** 
 * オブジェクトの着色状態.
 * インクリメンタルGCのためのフラグです。
 */
typedef enum ObjectPaint {
	PAINT_UNMARKED_T,
	PAINT_MARKED_T,
	//コンテキストが終了するまで
	//GCの対象にならない
	//ソースコード中に直接記述されたリテラルのためのフラグ。
	PAINT_ONEXIT_T,
//	paint_white,
//	paint_black,
//	paint_gray
} ObjectPaint ;

/**
 * オブジェクトの種類を表す列挙.
 */
typedef enum object_tag {
	OBJECT_INT_T,
	OBJECT_LONG_T, //bc_timeでだけ使ってる
	OBJECT_DOUBLE_T,
	OBJECT_CHAR_T,
	OBJECT_STRING_T,
	OBJECT_BOOL_T,
	OBJECT_REF_T,
	OBJECT_ARRAY_T,
	OBJECT_NULL_T,
} object_tag;

/**
 * ヒープに関連付けされるオブジェクト.
 * signal で使用される全てのデータはこれ。
 */
typedef struct object {
	struct generic_type* gtype;
	struct VTable* vptr;
	ObjectPaint paint;
	object_tag tag;
	Vector* native_slot_vec;
	bool is_coroutine;
	bool is_clone;
	union {
		int int_;
		double double_;
#if defined(_MSC_VER)
		__int64 long_;
#else
		long long_;
#endif
		char char_;
//		char* string_;
		bool bool_;
		Vector* field_vec;
	} u;
} object;

/**
 * 整数型のオブジェクトを作成します.
 * @param i
 * @return
 */
#define object_int_new(i) (MallocIntObject(i, __FILE__, __LINE__))
object* MallocIntObject(int i, const char* filename, int lineno);

/**
 * 可能ならキャッシュを返します.
 * @param i
 * @return
 */
object* GetIntObject(int i);

/**
 * 浮動小数型のオブジェクトを作成します.
 * @param d
 * @return
 */
#define object_double_new(d) (MallocDoubleObject(d, __FILE__, __LINE__))
object* MallocDoubleObject(double d, const char* filename, int lineno);

/**
 * long型の値を作成します.
 * @param l
 * @return
 */
#define object_long_new(l) (MallocLongObject(l, __FILE__, __LINE__))
object* MallocLongObject(long l, const char* filename, int lineno);

/**
 * 文字型のオブジェクトを作成します.
 * @param c
 * @return
 */
#define object_char_new(c) (MallocCharObject(c, __FILE__, __LINE__))
object* MallocCharObject(char c, const char* filename, int lineno);

/**
 * 文字列型のオブジェクトを作成します.
 * @param s
 * @return
 */
#define object_string_new(s) (MallocStringObject(s, __FILE__, __LINE__))
object* MallocStringObject(const char* s, const char* filename, int lineno);

/**
 * 参照型のオブジェクトを作成します.
 * @return
 */
#define object_ref_new() (MallocRefObject(__FILE__, __LINE__))
object* MallocRefObject(const char* filename, int lineno);

/**
 * 真偽値型の値を参照します.
 * @param b
 * @return
 */
object* GetBoolObject(bool b);

/**
 * trueを参照します.
 * @return
 */
object* GetTrueObject();

/**
 * falseを参照します.
 * @return
 */
object* GetFalseObject();

/**
 * nullを参照します.
 * @return
 */
object* GetNullObject();

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を +1 します.
 * @param self
 */
void IncObject(object* self);

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を -1 します.
 * @param self
 */
void DecObject(object* self);

/**
 * このオブジェクトを複製します.
 * int/double/char/boolでのみ使用可能です。
 * @param self
 * @return
 */
object* CopyObject(object* self);

/**
 * 参照としてオブジェクトを複製します.
 * @param self
 * @return
 */
object* CloneObject(object* self);

/**
 * このオブジェクトと
 * このオブジェクトから参照可能なオブジェクトを全てマークします.
 * @param self
 * @param paint
 */
void PaintAllObject(object* self, ObjectPaint paint);

/**
 * このオブジェクトと
 * このオブジェクトから参照可能なオブジェクトを全てマークします.
 * @param self
 */
void MarkAllObject(object* self);

/**
 * まだ開放されていないオブジェクトの数を返します.
 * @return
 */
int CountActiveObject();

/**
 * オブジェクトの詳細を出力します.
 * @param self
 */
void PrintObject(object* self);

/**
 * オブジェクトを開放します.
 * @param self
 */
void DeleteObject(object* self);

/**
 * 定数などを解放するための関数.
 * @param self
 */
void DestroyObject(object* self);

/**
 * beaconからCの int へ変換します.
 * @param self
 * @return
 */
int ObjectToInt(object* self);

/**
 * beaconからCの double へ変換します.
 * @param self
 * @return
 */
double ObjectToDouble(object* self);

/**
 * beaconからCの bool へ変換します.
 * @param self
 * @return
 */
bool ObjectToBool(object* self);

/**
 * beaconからCの char へ変換します.
 * @param self
 * @return
 */
char ObjectToChar(object* self);

/**
 * beaconからCの long へ変換します.
 * @param self
 * @return
 */
long ObjectToLong(object* self);

/**
 * Cからbeaconの Int へ変換します.
 * @param i
 * @return
 */
object* IntToObject(int i);

/**
 * Cからbeaconの Double へ変換します.
 * @param d
 * @return
 */
object* DoubleToObject(double d);

/**
 * Cからbeaconの bool へ変換します.
 * @param b
 * @return
 */
object* BoolToObject(bool b);

/**
 * Cからbeaconの char へ変換します.
 * @param c
 * @return
 */
object* CharToObject(char c);

/**
 * Cからbeacon
 * @param l
 * @return
 */
object* LongToObject(long l);

/**
 * 指定の型のデフォルト値を返します.
 * @param gt
 * @return
 */
object* GetDefaultObject(struct generic_type* gt);

/**
 * このオブジェクトのデバッグ表現を返します.
 * @param self
 * @return
 */
const char* GetObjectName(object* self);
#endif // !SIGNAL_ENV_OBJECT_H
