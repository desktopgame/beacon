#pragma once
#ifndef SIGNAL_PARSER_CLASS_LOADER_H
#define SIGNAL_PARSER_CLASS_LOADER_H
#include "../ast/ast.h"
#include "content_type.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * クラスローダーを表す構造体です.
 */
typedef struct class_loader {
	ast* source_code;
	struct class_loader* parent;
	content_type type;
	uint32_t ref_count;
	bool fail;
} class_loader;

/**
 * エントリポイントを示すクラスローダーを作成します.
 * @param filename
 * @return
 */
class_loader* class_loader_new_entry_point(const char* filename);

/**
 * ファイルの内容を解析して必要に応じてインポート先のファイルの読み込み、
 * 型の解決などその他必要な情報をまとめあげます。
 * @param self
 */
void class_loader_load(class_loader* self);

/**
 * このクラスローダーを開放します.
 * @param self
 */
void class_loader_delete(class_loader* self);
#endif // !SIGNAL_PARSER_CLASS_LOADER_H
