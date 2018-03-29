#pragma once
#ifndef BEACON_PARSER_CLASS_LOADER_H
#define BEACON_PARSER_CLASS_LOADER_H
#include "../ast/ast.h"
#include "content_type.h"
#include "import_manager.h"
#include "../il/il_top_level.h"
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
	//struct class_loader* parent;
	struct enviroment* env;
	import_manager* import_manager;
	content_type type;
	vector* type_cache_vec;
	struct class_loader* parent;
	int level;
	bool loaded_namespace;
	bool linked_allimports;
	char* filename;
	char* error_message;
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
class_loader* class_loader_new_entry_point_from_file(const char* filename);

/**
 * エントリポイントを示すクラスローダーを作成します.
 * @param source
 * @param contextDescription
 * @return
 */
class_loader* class_loader_new_entry_point_from_source(const char* source, const char* contextDescription);

/**
 * エントリポイントを示すクラスローダーを作成します.
 * @param p 呼び出し側で pop() してください
 * @return
 */
class_loader* class_loader_new_entry_point_from_parser(struct parser* p);

/**
 * ファイルの内容を解析して必要に応じてインポート先のファイルの読み込み、
 * 型の解決などその他必要な情報をまとめあげます。
 * @param self
 */
void class_loader_load(class_loader* self);

/**
 * self を 親として fullPath のファイルを読み込みます.
 * @param self
 * @parma fullPath
 */
void class_loader_sub(class_loader* self, char* fullPath);

/**
 * 実行時ディレクトリからの相対パスでファイルを読み込みます.
 * @param self
 * @param rpath
 */
void class_loader_rsub(class_loader* self, char* relativePath);

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

/**
 * ブートストラップクラスローダーを返します.
 * @return
 */
class_loader* class_loader_bootstrap();

//void class_link_print(class_link link);
#endif // !SIGNAL_PARSER_CLASS_LOADER_H
