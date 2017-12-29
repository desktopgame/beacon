#pragma once
#ifndef SIGNAL_VM_CONSTANT_ELEMENT_H
#define SIGNAL_VM_CONSTANT_ELEMENT_H
/**
 * 定数プール内の要素の種類を表す列挙型.
 */
typedef enum constant_type {
	constant_int,
	constant_double,
	constant_char,
	constant_string,
} constant_type;

/**
 * 定数プール内の要素を表します.
 * これ自体を vector に格納することで、
 * インデックスから定数を逆引き出来るようにします。
 * そのまま値を格納しないのは、double型(8byte)を格納するためです。
 */
typedef struct constant_element {
	constant_type type;
	union {
		int int_;
		double double_;
		char char_;
		char* string_;
	} u;
} constant_element;

/**
 * 整数型の定数を作成します.
 * @param i
 * @return
 */
constant_element* constant_int_new(int i);

/**
 * 浮動小数型の定数を作成します.
 * @param d
 * @return
 */
constant_element* constant_double_new(double d);

/**
 * 文字型の定数を作成します.
 * @param c
 * @return
 */
constant_element* constant_char_new(char c);

/**
 * 文字列型の定数を作成します.
 * @param s 複製されます。
 * @return
 */
constant_element* constant_string_new(const char* s);

/**
 * 定数を開放します.
 * この定数が格納しているオブジェクトが文字列ならそれも開放します.
 * @param self
 */
void constant_element_delete(constant_element* self);
#endif // !SIGNAL_VM_CONSTANT_ELEMENT_H
