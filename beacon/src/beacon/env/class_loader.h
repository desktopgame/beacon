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
	bool error;
} class_loader;

/**
 * クラスローダーのエラーを表すID.
 */
typedef enum cl_error_id {
	clerror_parse,
	clerror_class_first,
	clerror_multi_eqinterface,
	clerror_interface_only,
	clerror_chain,
	clerror_modifier_a_overlapped,
	clerror_field_name_a_overlapped,
	clerror_native_field,
	clerror_abstract_method_by,
	clerror_empty_method_body,
	clerror_not_empty_method_body,
	clerror_not_implement_interface,
	clerror_not_implement_abstract_method,
	clerror_private_operator,
	clerror_illegal_argument_bioperator,
	clerror_illegal_argument_uoperator,
} cl_error_id;

/**
 * 引数のクラスローダの error が true なら return します.
 * @param self
 */
#define CL_ERROR(self) if((self)->error || bc_error_last()) return

/**
 * 引数のクラスローダの error が true なら a を return します.
 * @param self
 * @param a
 * @return
 */
#define CL_ERROR_RET(self, a) if((self)->error) return (a)

/**
 * クラスローダーを作成します.
 * @param type
 * @return
 */
class_loader* class_loader_new(content_type type);

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

/**
 * ブートストラップクラスローダーを返します.
 * @return
 */
class_loader* class_loader_bootstrap();

//void class_link_print(class_link link);
#endif // !SIGNAL_PARSER_CLASS_LOADER_H
