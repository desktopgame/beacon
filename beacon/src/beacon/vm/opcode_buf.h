#pragma once
#ifndef BEACON_VM_OPCODE_BUF_H
#define BEACON_VM_OPCODE_BUF_H
#include "../util/vector.h"
#include "label.h"
#include "opcode.h"
/**
 * オペコードの一覧を表す構造体.
 */
typedef struct OpcodeBuf {
	Vector* Instructions;
	Vector* LabelTable;
} OpcodeBuf;

/**
 * オペコードの一覧を作成します.
 * @return
 */
OpcodeBuf* NewOpcodeBuf();

/**
 * self->source に item を追加します.
 * @param self
 * @param item
 * @return
 */
int AddOpcodeBuf(OpcodeBuf* self, VectorItem item);

/**
 * このバッファーの開放時に開放されるラベルを作成します.
 * @param index
 * @return
 */
Label* AddLabelOpcodeBuf(OpcodeBuf * self, int index);

/**
 * nop を追加してその位置を返します.
 * @param self
 * @return
 */
int AddNOPOpcodeBuf(OpcodeBuf* self);

/**
 * オペコードの一覧を出力します.
 * @param self
 * @param depth
 */
void DumpOpcodeBuf(OpcodeBuf* self, int depth);

/**
 * a の 末尾に b を統合した新しい OpcodeBuf を作成します.
 * @param a
 * @param b
 * @return
 */
OpcodeBuf* MergeOpcodeBuf(OpcodeBuf* a, OpcodeBuf* b);

/**
 * オペコードの一覧を開放します.
 * @param self
 */
void DeleteOpcodeBuf(OpcodeBuf* self);
#endif // !SIGNAL_VM_OPCODE_BUF_H
