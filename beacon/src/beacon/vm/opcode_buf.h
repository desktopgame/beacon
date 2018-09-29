#pragma once
#ifndef BEACON_VM_OPCODE_BUF_H
#define BEACON_VM_OPCODE_BUF_H
#include "../util/vector.h"
#include "label.h"
#include "opcode.h"
/**
 * オペコードの一覧を表す構造体.
 */
typedef struct opcode_buf {
	Vector* source_vec;
	Vector* label_vec;
} opcode_buf;

/**
 * オペコードの一覧を作成します.
 * @return
 */
opcode_buf* NewOpcodeBuf();

/**
 * self->source に item を追加します.
 * @param self
 * @param item
 * @return
 */
int AddOpcodeBuf(opcode_buf* self, VectorItem item);

/**
 * このバッファーの開放時に開放されるラベルを作成します.
 * @param index
 * @return
 */
label* AddLabelOpcodeBuf(opcode_buf * self, int index);

/**
 * nop を追加してその位置を返します.
 * @param self
 * @return
 */
int AddNOPOpcodeBuf(opcode_buf* self);

/**
 * オペコードの一覧を出力します.
 * @param self
 * @param depth
 */
void DumpOpcodeBuf(opcode_buf* self, int depth);

/**
 * a の 末尾に b を統合した新しい opcode_buf を作成します.
 * @param a
 * @param b
 * @return
 */
opcode_buf* MergeOpcodeBuf(opcode_buf* a, opcode_buf* b);

/**
 * オペコードの一覧を開放します.
 * @param self
 */
void DeleteOpcodeBuf(opcode_buf* self);
#endif // !SIGNAL_VM_OPCODE_BUF_H
