#pragma once
#ifndef SIGNAL_PARSE_PARSER_H
#define SIGNAL_PARSE_PARSER_H
#include "../ast/ast.h"
#include "yacc_input_type.h"
#include <stdbool.h>

/**
 * Yacc/Bisonの解析結果を保存する構造体です.
 */
typedef struct parser {
	ast* root;
	char* buffer;
	//char* source;
	char* source_name;
	char* errorLineText;
	char* errorMessage;
	int errorLineIndex;
	int errorColumnIndex;
	yacc_input_type input_type;
	bool fail;
} parser;

/**
 * 新しいパーサーをプッシュします.
 * @param input_type
 */
parser* parser_push(yacc_input_type input_type);

/**
 * 現在のパーサーを返します.
 */
parser* parser_top();

/**
 * バッファーをクリアします.
 * @param self
 */
void parser_clear_buffer(parser* self);

/**
 * 指定の文字を現在のバッファーへ追加します.
 * @parma self
 * @param ch
 */
void parser_append_buffer(parser* self, char ch);

/**
 * バッファーを文字列リテラルをASTへ還元します.
 * @param self
 * @return
 */
ast* parser_reduce_buffer(parser* self);

/**
 * ファイルを入力として解析を実行します.
 * パーサースタックは +1 されます。
 * @param filename
 * @return
 */
parser* parser_parse_from_file(const char* filename);

/**
 * 文字を入力として解析を実行します.
 * パーサースタックは +1 されます。
 * @param source 呼び出し側で開放してください.
 * @return
 */
parser* parser_parse_from_source(char* source);

/**
 * 情報を入れ替えてからパースします.
 * @param source
 * @param info
 * @return
 */
parser* parser_parse_from_source_swap(char* source, char* info);

/**
 * デバッグ情報として使用される入力元の情報を設定します.
 * 以前の情報は開放されます。
 * また、この時渡す引数は呼び出し側で開放してください。
 * @param source_name
 */
void parser_swap_source_name(char* source_name);

/**
 * エラー情報を表示します.
 * @param p
 */
void parser_print_error(parser* p);

/**
 * 現在のパーサーを削除します.
 * パーサースタックは -1 されます。
 * また、このときパーサが持っているASTは開放されます。
 */
void parser_pop();
#endif // !SIGNAL_PARSE_PARSER_H
