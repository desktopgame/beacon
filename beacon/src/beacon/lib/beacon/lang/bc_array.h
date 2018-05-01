#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
#define BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
struct vm;
struct type;
struct object;

/**
 * beacon::lang::Arrayクラスを初期化します.
 */
void bc_array_init();

/**
 * beacon::lang::Arrayクラスを返します.
 * @return
 */
struct type* bc_array_class();

/**
 * beacon::lang::Arrayクラスを作成します.
 * @param length
 * @param vmc
 * @return
 */
struct object* bc_array_new(int length, struct vm* vmc);

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
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
