#pragma once
#ifndef BEACON_PARSE_PARSER_H
#define BEACON_PARSE_PARSER_H
#include "../ast/ast.h"
#include "yacc_input_type.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * Yacc/Bisonの解析結果を保存する構造体です.
 */
typedef struct parser {
	ast* root;
	string_buffer* literal_buffer;
	//char* source;
	char* source_name;
	char* error_line_text;
	char* error_message;
	int error_line_index;
	int error_column_index;
	yacc_input_type input_type;
	bool fail;
	int lineno;
	vector* lineno_vec;
} parser;

/**
 * 文字列を入力として構文解析を実行します.
 * 必ず parser_destroy で解放する必要があります。
 * @param source
 * @return
 */
parser* parse_string(const char* source);

/**
 * ファイルを入力として構文解析を実行します.
 * 必ず parser_destroy で解放する必要があります。
 * @param source
 * @return
 */
parser* parse_file(const char* filename);

/**
 * 現在のパーサーを返します.
 * @return
 */
parser* parser_current();

/**
 * エラー情報とASTを解放します.
 * @param self
 */
void parser_destroy(parser* self);

/**
 * 文字列バッファーをクリアします.
 * @param self
 */
void parser_clear_buffer(parser* self);

/**
 * 文字列バッファーに一文字加算します.
 * @param self
 * @return
 */
void parser_append_buffer(parser* self, char ch);

/**
 * 文字列バッファーをリテラルノードへ還元します.
 * @param self
 * @return
 */
ast* parser_reduce_buffer(parser* self);

/**
 * パーサーからASTを取り上げて解放させないようにします.
 * 解析が終わった後、まだASTが必要ならこれを使用します。
 * @param self
 * @return
 */
ast* parser_release_ast(parser* self);

/**
 * エラー情報を出力します.
 * @param p
 */
void parser_print_error(parser* p);
#endif // !SIGNAL_PARSE_PARSER_H
