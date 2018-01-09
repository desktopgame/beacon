#pragma once
#ifndef SIGNAL_PARSER_CLASS_LOADER_H
#define SIGNAL_PARSER_CLASS_LOADER_H
#include "../ast/ast.h"
#include "content_type.h"
#include "import_manager.h"
#include "../il/il_top_level.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
struct enviroment;

/**
 * クラスローダーを表す構造体です.
 */
typedef struct class_loader {
	ast* source_code;
	il_top_level* il_code;
	struct class_loader* parent;
	struct enviroment* env;
	import_manager* import_manager;
	content_type type;
	uint32_t ref_count;
	char* errorMessage;
	bool error;
} class_loader;

/**
 * クラスローダーを作成します.
 * @return
 */
class_loader* class_loader_new();

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

/**
 * エラーを報告します.
 * @param self
 * @param message
 */
void class_loader_error(class_loader* self, const char* message);

/**
 * エラーをフォーマット付きで報告します.
 * @param self
 * @param message
 * @param ...
 */
void class_loader_errorf(class_loader* self, const char* message, ...);
#endif // !SIGNAL_PARSER_CLASS_LOADER_H
