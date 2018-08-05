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

parser* parse_string(const char* source);

parser* parse_file(const char* filename);

parser* parser_current();

void parser_destroy(parser* self);

void parser_clear_buffer(parser* self);

void parser_append_buffer(parser* self, char ch);

ast* parser_reduce_buffer(parser* self);

ast* parser_release_ast(parser* self);

void parser_print_error(parser* p);
#endif // !SIGNAL_PARSE_PARSER_H
