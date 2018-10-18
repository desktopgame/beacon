#pragma once
#ifndef BEACON_VM_LABEL_H
#define BEACON_VM_LABEL_H

/**
 * goto の引数として使用します。
 * ジャンプ先が後方であるとき、これを使用して前方参照します。
 */
typedef struct Label {
	int Cursor;
} Label;

/**
 * ラベルを作成します.
 * @param cursor
 * @return
 */
Label* NewLabel(int cursor);

/**
 * ラベルを複製します.
 * @param src
 * @return
 */
Label* CloneLabel(Label* src);

/**
 * ラベルを開放します.
 * @param self
 */
void DeleteLabel(Label* self);
#endif // !SIGNAL_VM_LABEL_H
