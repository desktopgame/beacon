#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
#define BEACON_LIB_SIGNAL_LANG_SG_ARRAY_H
struct Frame;
struct type;
struct Object;
struct generic_type;

/**
 * beacon::lang::Arrayクラスを初期化します.
 */
void InitBCArray();

/**
 * beacon::lang::Arrayクラスを返します.
 * @return
 */
struct type* GetBCArrayType();

/**
 * beacon::lang::Arrayクラスを作成します.
 * @param gtype
 * @param length
 * @param fr
 * @return
 */
struct Object* NewBCArray(struct generic_type* gtype, int length, struct Frame* fr);

/**
 * @param arr
 * @param index
 * @param o
 * @return
 */
void SetBCArray(struct Object* arr, int index, struct Object* o);

/**
 * @param arr
 * @param index
 * @return
 */
struct Object* GetBCArray(struct Object* arr, int index);

/**
 * @param arr
 * @return
 */
int GetLengthBCArray(struct Object* arr);
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_ARRAY_H
