#ifndef BEACON_VM_LAZY_INT_H
#define BEACON_VM_LAZY_INT_H
/**
 * あとで解決されるインデックスのための構造体.
 * 例えば動的生成される== != 演算子はオペコード生成時点ではインデックスが不定なので、
 * とりあえずこれを入れておきます。
 */
typedef struct lazy_int {
	int value;
} lazy_int;

/**
 * 指定の値で lazy_int を生成します.
 * @param value
 * @return
 */
lazy_int* lazy_int_new(int value);

/**
 * lazy_int を解放します.
 * @param self
 */
void lazy_int_delete(lazy_int* self);
#endif