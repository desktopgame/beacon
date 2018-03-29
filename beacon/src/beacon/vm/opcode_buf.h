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
	vector* source;
	vector* labels;
} opcode_buf;

/**
 * オペコードの一覧を作成します.
 * @return
 */
opcode_buf* opcode_buf_new();

/**
 * self->source に item を追加します.
 * @param self
 * @param item
 */
void opcode_buf_add(opcode_buf* self, vector_item item);

/**
 * このバッファーの開放時に開放されるラベルを作成します.
 * @param index
 * @return
 */
label* opcode_buf_label(opcode_buf * self, int index);

/**
 * nop を追加してその位置を返します.
 * @param self
 * @return
 */
int opcode_buf_nop(opcode_buf* self);

/**
 * オペコードの一覧を出力します.
 * @param self
 * @param depth
 */
void opcode_buf_dump(opcode_buf* self, int depth);

/**
 * a の 末尾に b を統合した新しい opcode_buf を作成します.
 * @param a
 * @param b
 * @return
 */
opcode_buf* opcode_buf_merge(opcode_buf* a, opcode_buf* b);

/**
 * オペコードの一覧を開放します.
 * @param self
 */
void opcode_buf_delete(opcode_buf* self);
#endif // !SIGNAL_VM_OPCODE_BUF_H
