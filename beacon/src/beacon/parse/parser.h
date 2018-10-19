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
 * 解析の結果を表す構造体.
 */
typedef enum ParseResult {
	PARSE_AWAIT_T = -1,
	PARSE_COMPLETE_T = 0,
	PARSE_OPEN_ERROR_T,
	PARSE_SYNTAX_ERROR_T
} ParseResult;

/**
 * Yacc/Bisonの解析結果を保存する構造体です.
 */
typedef struct parser {
	ast* root;
	Buffer* literal_buffer;
	//char* source;
	char* source_name;
	char* error_line_text;
	char* error_message;
	int error_line_index;
	int error_column_index;
	YaccInputType input_type;
	ParseResult result;
	int lineno;
	Vector* lineno_vec;
} parser;

/**
 * 文字列を入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
parser* ParseString(const char* source);

/**
 * ファイルを入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
parser* ParseFile(const char* filename);

/**
 * 現在のパーサーを返します.
 * @return
 */
parser* GetCurrentParser();

/**
 * エラー情報とASTを解放します.
 * @param self
 */
void DestroyParser(parser* self);

/**
 * 文字列バッファーをクリアします.
 * @param self
 */
void ClearParserBuffer(parser* self);

/**
 * 文字列バッファーに一文字加算します.
 * @param self
 * @return
 */
void AppendParserBuffer(parser* self, char ch);

/**
 * 文字列バッファーをリテラルノードへ還元します.
 * @param self
 * @return
 */
ast* ReduceParserBuffer(parser* self);

/**
 * パーサーからASTを取り上げて解放させないようにします.
 * 解析が終わった後、まだASTが必要ならこれを使用します。
 * @param self
 * @return
 */
ast* ReleaseParserAST(parser* self);

/**
 * エラー発生位置を設定します.
 * @param p
 */
void RelocationParserError(parser* p);
#endif // !SIGNAL_PARSE_PARSER_H
