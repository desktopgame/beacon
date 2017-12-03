#pragma once
#ifndef SIGNAL_PARSE_PARSER_H
#define SIGNAL_PARSE_PARSER_H
#include "../ast/ast.h"
#include "yacc_input_type.h"
#include <stdbool.h>

typedef struct parser {
	ast* root;
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
* ファイルを入力として解析を実行します.
* @param filename
* @return
*/
parser* parser_parse_from_file(const char* filename);

/**
 * 文字を入力として解析を実行します.
 * @param source
 * @return
 */
parser* parser_parse_from_source(char* source);

/**
 * 現在のパーサーを削除します.
 */
void parser_pop();
#endif // !SIGNAL_PARSE_PARSER_H
