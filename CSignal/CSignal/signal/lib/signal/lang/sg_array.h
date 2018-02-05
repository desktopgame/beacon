#pragma once
#ifndef SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
#define SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
struct vm;
struct type;
struct object;

/**
 * signal::lang::Arrayクラスを初期化します.
 */
void sg_array_init();

/**
 * signal::lang::Arrayクラスを返します.
 * @return
 */
struct type* sg_array_class();

/**
 * signal::lang::Arrayクラスを作成します.
 * @param length
 * @param vmc
 * @return
 */
struct object* sg_array_new(int length, struct vm* vmc);

/**
 * @param arr
 * @param index
 * @param o
 * @return
 */
void sg_array_set(struct object* arr, int index, struct object* o);

/**
 * @param arr
 * @param index
 * @return
 */
struct object* sg_array_get(struct object* arr, int index);
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
