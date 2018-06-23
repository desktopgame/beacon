#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
#define BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
struct frame;
struct type;
struct object;
struct generic_type;

/**
 * beacon::lang::Arrayクラスを初期化します.
 */
void bc_array_init();

/**
 * beacon::lang::Arrayクラスを返します.
 * @return
 */
struct type* bc_array_type();

/**
 * beacon::lang::Arrayクラスを作成します.
 * @param gtype
 * @param length
 * @param fr
 * @return
 */
struct object* bc_array_new(struct generic_type* gtype, int length, struct frame* fr);

/**
 * @param arr
 * @param index
 * @param o
 * @return
 */
void bc_array_set(struct object* arr, int index, struct object* o);

/**
 * @param arr
 * @param index
 * @return
 */
struct object* bc_array_get(struct object* arr, int index);

/**
 * @param arr
 * @return
 */
int bc_array_length(struct object* arr);
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
