#include "parser.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/string_pool.h"
#include "../ast/ast.h"
#include "../ast/ast_new_literal.h"
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
	text_stdout_enabled(false);
	if (yyparse()) {
		yy_clearstr();
		gParser->fail = true;
		text_stdout_enabled(true);
		parser_print_error(gParser);
		return gParser;
	}
	yy_clearstr();
	return gParser;
}

parser* parse_file(const char* filename) {
	assert(gParser == NULL);
	extern int yyparse(void);
	extern FILE *yyin;
	yyin = fopen(filename, "r");
	gParser = parser_new();
	gParser->source_name = text_strdup(filename);
	//対象のファイルを開けなかった
	if(!yyin) {
		return gParser;
	}
	text_stdout_enabled(false);
	if (yyparse()) {
		gParser->fail = true;
		text_stdout_enabled(true);
		parser_print_error(gParser);
		return gParser;
	}
	text_stdout_enabled(true);
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

void parser_print_error(parser* p) {
	text_printf("file=%s ", p->source_name);
	text_printf("line=%d ", p->error_line_index);
	text_printf("column=%d", p->error_column_index);
	text_putline();

	text_printf("%s", p->error_message);
	text_putline();

	text_printf("%s", p->error_line_text);
	text_putline();
	fflush(stdout);
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
	ret->fail = false;
	ret->lineno = 0;
	ret->literal_buffer = NULL;
	ret->lineno_vec = vector_new();
	ret->root = ast_new(ast_root);
	return ret;
}