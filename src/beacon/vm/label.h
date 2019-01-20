// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file label.h
 * @brief gotoのジャンプ先を指定するラベルを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_VM_LABEL_H
#define BEACON_VM_LABEL_H

/**
 * goto の引数として使用します。
 * ジャンプ先が後方であるとき、これを使用して前方参照します。
 */
typedef struct bc_Label {
        int Cursor;
} bc_Label;

/**
 * ラベルを作成します.
 * @param cursor
 * @return
 */
bc_Label* bc_NewLabel(int cursor);

/**
 * ラベルを開放します.
 * @param self
 */
void bc_DeleteLabel(bc_Label* self);
#endif  // !SIGNAL_VM_LABEL_H
