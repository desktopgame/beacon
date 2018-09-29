#ifndef BEACON_VM_GENERATE_H
#define BEACON_VM_GENERATE_H
#include "opcode_buf.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/property.h"

/**
 * フィールドを取得するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GenerateGetField(opcode_buf* buf, field* fi, int index);

/**
 * プロパティを取得するオペコードを生成します.
 * @param buf
 * @param prop
 * @param index
 */
void GenerateGetProperty(opcode_buf* buf, property* prop, int index);

/**
 * フィールドに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GeneratePutField(opcode_buf* buf, field* fi, int index);
/**
 * プロパティに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GeneratePutProperty(opcode_buf* buf, property* prop, int index);
#endif