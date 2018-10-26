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
typedef enum ObjectTag {
	OBJECT_INT_T,
	OBJECT_LONG_T, //bc_timeでだけ使ってる
	OBJECT_DOUBLE_T,
	OBJECT_CHAR_T,
	OBJECT_STRING_T,
	OBJECT_BOOL_T,
	OBJECT_REF_T,
	OBJECT_ARRAY_T,
	OBJECT_NULL_T,
} ObjectTag;

/**
 * ヒープに関連付けされるオブジェクト.
 * signal で使用される全てのデータはこれ。
 */
typedef struct Object {
	struct generic_type* GType;
	struct VTable* VPtr;
	ObjectPaint Paint;
	ObjectTag Tag;
	Vector* NativeSlotVec;
	bool IsCoroutine;
	bool IsClone;
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
} Object;

/**
 * 整数型のオブジェクトを作成します.
 * @param i
 * @return
 */
#define Object_int_new(i) (MallocIntObject(i, __FILE__, __LINE__))
Object* MallocIntObject(int i, const char* filename, int lineno);

/**
 * 可能ならキャッシュを返します.
 * @param i
 * @return
 */
Object* GetIntObject(int i);

/**
 * 浮動小数型のオブジェクトを作成します.
 * @param d
 * @return
 */
#define Object_double_new(d) (MallocDoubleObject(d, __FILE__, __LINE__))
Object* MallocDoubleObject(double d, const char* filename, int lineno);

/**
 * long型の値を作成します.
 * @param l
 * @return
 */
#define Object_long_new(l) (MallocLongObject(l, __FILE__, __LINE__))
Object* MallocLongObject(long l, const char* filename, int lineno);

/**
 * 文字型のオブジェクトを作成します.
 * @param c
 * @return
 */
#define Object_char_new(c) (MallocCharObject(c, __FILE__, __LINE__))
Object* MallocCharObject(char c, const char* filename, int lineno);

/**
 * 文字列型のオブジェクトを作成します.
 * @param s
 * @return
 */
#define Object_string_new(s) (MallocStringObject(s, __FILE__, __LINE__))
Object* MallocStringObject(const char* s, const char* filename, int lineno);

/**
 * 参照型のオブジェクトを作成します.
 * @return
 */
#define Object_ref_new() (MallocRefObject(__FILE__, __LINE__))
Object* MallocRefObject(const char* filename, int lineno);

/**
 * 真偽値型の値を参照します.
 * @param b
 * @return
 */
Object* GetBoolObject(bool b);

/**
 * trueを参照します.
 * @return
 */
Object* GetTrueObject();

/**
 * falseを参照します.
 * @return
 */
Object* GetFalseObject();

/**
 * nullを参照します.
 * @return
 */
Object* GetNullObject();

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を +1 します.
 * @param self
 */
void IncObject(Object* self);

/**
 * このオブジェクトが数値型なら、
 * 内部の数値を -1 します.
 * @param self
 */
void DecObject(Object* self);

/**
 * このオブジェクトを複製します.
 * int/double/char/boolでのみ使用可能です。
 * @param self
 * @return
 */
Object* CopyObject(Object* self);

/**
 * 参照としてオブジェクトを複製します.
 * @param self
 * @return
 */
Object* CloneObject(Object* self);

/**
 * このオブジェクトと
 * このオブジェクトから参照可能なオブジェクトを全てマークします.
 * @param self
 * @param paint
 */
void PaintAllObject(Object* self, ObjectPaint paint);

/**
 * このオブジェクトと
 * このオブジェクトから参照可能なオブジェクトを全てマークします.
 * @param self
 */
void MarkAllObject(Object* self);

/**
 * まだ開放されていないオブジェクトの数を返します.
 * @return
 */
int CountActiveObject();

/**
 * オブジェクトの詳細を出力します.
 * @param self
 */
void PrintObject(Object* self);

/**
 * オブジェクトを開放します.
 * @param self
 */
void DeleteObject(Object* self);

/**
 * 定数などを解放するための関数.
 * @param self
 */
void DestroyObject(Object* self);

/**
 * beaconからCの int へ変換します.
 * @param self
 * @return
 */
int ObjectToInt(Object* self);

/**
 * beaconからCの double へ変換します.
 * @param self
 * @return
 */
double ObjectToDouble(Object* self);

/**
 * beaconからCの bool へ変換します.
 * @param self
 * @return
 */
bool ObjectToBool(Object* self);

/**
 * beaconからCの char へ変換します.
 * @param self
 * @return
 */
char ObjectToChar(Object* self);

/**
 * beaconからCの long へ変換します.
 * @param self
 * @return
 */
long ObjectToLong(Object* self);

/**
 * Cからbeaconの Int へ変換します.
 * @param i
 * @return
 */
Object* IntToObject(int i);

/**
 * Cからbeaconの Double へ変換します.
 * @param d
 * @return
 */
Object* DoubleToObject(double d);

/**
 * Cからbeaconの bool へ変換します.
 * @param b
 * @return
 */
Object* BoolToObject(bool b);

/**
 * Cからbeaconの char へ変換します.
 * @param c
 * @return
 */
Object* CharToObject(char c);

/**
 * Cからbeacon
 * @param l
 * @return
 */
Object* LongToObject(long l);

/**
 * 指定の型のデフォルト値を返します.
 * @param gt
 * @return
 */
Object* GetDefaultObject(struct generic_type* gt);

/**
 * このオブジェクトのデバッグ表現を返します.
 * @param self
 * @return
 */
const char* GetObjectName(Object* self);
#endif // !SIGNAL_ENV_OBJECT_H
