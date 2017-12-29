#pragma once
#ifndef SIGNAL_ENV_OBJECT_H
#define SIGNAL_ENV_OBJECT_H
#include "../util/vector.h"

struct class_;
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
typedef enum object_type {
	object_int,
	object_double,
	object_char,
	object_string,
	object_ref,
} object_type;

/**
 * ヒープに関連付けされるオブジェクト.
 * signal で使用される全てのデータはこれ。
 */
typedef struct object {
	//宣言時の型, 代入時の型を持つ
	//代入されるたびに更新される
	//代入されるとき、インデックスをどうにか変換
	struct class_* classz;
	object_paint paint;
	object_type type;
	union {
		int int_;
		double double_;
		char char_;
		char* string_;
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
 * オブジェクトとフィールドを開放します.
 * @param self
 */
void object_delete(object* self);
#endif // !SIGNAL_ENV_OBJECT_H
