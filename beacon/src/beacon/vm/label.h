#pragma once
#ifndef BEACON_VM_LABEL_H
#define BEACON_VM_LABEL_H

/**
 * goto の引数として使用します。
 * ジャンプ先が後方であるとき、これを使用して前方参照します。
 */
typedef struct label {
	int cursor;
} label;

/**
 * ラベルを作成します.
 * @param cursor
 * @return
 */
label* label_new(int cursor);

/**
 * ラベルを複製します.
 * @param src
 * @return
 */
label* label_clone(label* src);

/**
 * ラベルを開放します.
 * @param self
 */
void label_delete(label* self);
#endif // !SIGNAL_VM_LABEL_H
