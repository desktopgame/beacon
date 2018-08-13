#include "parser.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_pool.h"
#include "../ast/ast.h"
#include "../ast/ast_new_literal.h"
#include "../error.h"
#include <assert.h>
static parser* parser_new();
static parser* gParser;

parser* parse_string(const char* source) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	gParser = parser_new();
	gParser->source_name = "unknown";
	yy_setstr(text_strdup(source));
	if (yyparse()) {
		yy_clearstr();
		gParser->result = parse_syntax_error_T;
		parser_relocation_error(gParser);
		return gParser;
	}
	yy_clearstr();
	return gParser;
}

parser* parse_file(const char* filename) {
	assert(gParser == NULL);
	extern void yy_setstr(char *source);
	extern int yyparse(void);
	extern FILE *yyin;
	yy_setstr(NULL);
	yyin = fopen(filename, "r");
	gParser = parser_new();
	gParser->source_name = text_strdup(filename);
	//対象のファイルを開けなかった
	if(!yyin) {
		gParser->result = parse_open_error_T;
		return gParser;
	}
	if (yyparse()) {
		gParser->result = parse_syntax_error_T;
		parser_relocation_error(gParser);
		return gParser;
	}
	return gParser;
}

parser* parser_current() {
	return gParser;
}

void parser_destroy(parser* self) {
	assert(gParser != NULL);
	if (gParser->root) {
		ast_delete(gParser->root);
	}
	vector_delete(gParser->lineno_vec, vector_deleter_null);
	MEM_FREE(gParser->literal_buffer);
	MEM_FREE(gParser->source_name);
	MEM_FREE(gParser);
	gParser =  NULL;
}

void parser_clear_buffer(parser* self) {
	self->literal_buffer = NULL;
}

void parser_append_buffer(parser* self, char ch) {
	if (self->literal_buffer == NULL) {
		self->literal_buffer = string_buffer_new();
	}
	string_buffer_append(self->literal_buffer, ch);
}

ast* parser_reduce_buffer(parser* self) {
	//""のような空文字の場合
	if (self->literal_buffer == NULL) {
		return ast_new_string(string_pool_intern(""));
	}
	ast* ret = ast_new_string(string_pool_intern2(self->literal_buffer));
	self->literal_buffer = NULL;
	return ret;
}

ast* parser_release_ast(parser* self) {
	ast* ret = self->root;
	self->root = NULL;
	return ret;
}

void parser_relocation_error(parser* p) {
	bc_error_file(p->source_name);
	bc_error_line(p->error_line_index);
	bc_error_column(p->error_column_index);
}

//private
static parser* parser_new() {
	parser* ret = MEM_MALLOC(sizeof(parser));
	assert(gParser == NULL);
	gParser = ret;
	ret->source_name = NULL;
	ret->error_line_text = NULL;
	ret->error_line_index = -1;
	ret->error_column_index = -1;
	ret->input_type = yinput_file;
	ret->result = parse_await;
	ret->lineno = 0;
	ret->literal_buffer = NULL;
	ret->lineno_vec = vector_new();
	ret->root = ast_new(ast_root);
	return ret;
}