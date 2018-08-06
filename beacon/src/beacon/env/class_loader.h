#pragma once
#ifndef BEACON_PARSER_CLASS_LOADER_H
#define BEACON_PARSER_CLASS_LOADER_H
#include "../ast/ast.h"
#include "content_type.h"
#include "import_manager.h"
#include "../il/il_top_level.h"
#include "link_type.h"
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
struct enviroment;
struct parser;

/**
 * クラスローダーを表す構造体です.
 */
typedef struct class_loader {
	ast* source_code;
	il_top_level* il_code;

	struct enviroment* env;
	import_manager* import_manager;
	content_type type;
	link_type link;
	vector* type_cache_vec;
	vector* lazy_resolve_vec;

	struct class_loader* parent;
	int level;
	char* filename;
//	bool error;
} class_loader;

/**
 * 引数のクラスローダの error が true なら return します.
 * @param self
 */
#define CL_ERROR(self) if(bc_error_last()) return

/**
 * 引数のクラスローダの error が true なら a を return します.
 * @param self
 * @param a
 * @return
 */
#define CL_ERROR_RET(self, a) if(bc_error_last()) return (a)

/**
 * クラスローダーを作成します.
 * @param filename
 * @param type
 * @return
 */
class_loader* class_loader_new(const char* filename, content_type type);

/**
 * ファイルの内容を解析して必要に応じてインポート先のファイルの読み込み、
 * 型の解決などその他必要な情報をまとめあげます。
 * @param self
 */
void class_loader_load(class_loader* self);

/**
 * 実行時ディレクトリからの相対パスでファイルを仮読み込みします.
 * beacon/langの読み込みのための使用されます。
 * @param self
 * @param relativePath
 */
void class_loader_special(class_loader* self, char* relativePath);

/**
 * このクラスローダーを開放します.
 * @param self
 */
void class_loader_delete(class_loader* self);

//void class_link_print(class_link link);
#endif // !SIGNAL_PARSER_CLASS_LOADER_H
