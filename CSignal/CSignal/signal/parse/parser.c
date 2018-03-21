#include "parser.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/text.h"
#include "../util/stack.h"
#include "../util/mem.h"
#include "../ast/ast_new_literal.h"
#include "../env/script_context.h"

parser * parser_push(yacc_input_type input_type) {
	script_context* ctx = script_context_get_current();
	if (ctx->parser_stack == NULL) {
		ctx->parser_stack = stack_new();
	}
	parser* p = (parser*)MEM_MALLOC(sizeof(parser));
	stack_push(ctx->parser_stack, p);
	p->input_type = input_type;
	p->lineno = 0;
	p->lineno_vec = vector_new();
	p->root = ast_new(ast_root);
	p->literal_buffer = NULL;
	p->error_line_index = 0;
	p->error_line_text = NULL;
	p->error_column_index = 0;
	p->error_message = NULL;
	p->source_name = text_strdup("unknown-source");
	p->fail = false;
	return p;
}

parser * parser_top() {
	script_context* ctx = script_context_get_current();
	if (ctx->parser_stack == NULL) {
		return NULL;
	}
	if (stack_empty(ctx->parser_stack)) {
		return NULL;
	}
	return (parser*)stack_top(ctx->parser_stack);
}

void parser_clear_buffer(parser * self) {
	self->literal_buffer = NULL;
}

void parser_append_buffer(parser * self, char ch) {
	if (self->literal_buffer == NULL) {
		self->literal_buffer = string_buffer_new();
	}
	string_buffer_append(self->literal_buffer, ch);
}

ast * parser_reduce_buffer(parser * self) {
	//""のような空文字の場合
	if (self->literal_buffer == NULL) {
		return ast_new_string(text_strdup(""));
	}
	string_buffer_shrink(self->literal_buffer);
	ast* ret = ast_new_string(self->literal_buffer->text);
	self->literal_buffer->text = NULL;
	MEM_FREE(self->literal_buffer);
	self->literal_buffer = NULL;
	return ret;
}

parser * parser_parse_from_file(const char * filename) {
	extern int yyparse(void);
	extern FILE *yyin;
#if defined(_MSC_VER)
	parser* p = parser_push(yinput_file);
	parser_swap_source_name(filename);
	errno_t err = fopen_s(&yyin, filename, "r");
	if (err != 0) {
		p->fail = true;
		return p;
	}
	if (yyparse()) {
		p->fail = true;
		parser_print_error(p);
		return p;
	}
	return p;
#else
	parser* p = parser_push(yinput_file);
	parser_swap_source_name(filename);
	yyin = fopen(filename, "r");
	if (!yyin) {
		p->fail = true;
		return p;
	}
	text_stdout_enabled(false);
	if (yyparse()) {
		p->fail = true;
		text_stdout_enabled(true);
		parser_print_error(p);
		return p;
	}
	text_stdout_enabled(true);
	return p;
#endif
}

parser * parser_parse_from_source(const char * source) {
	return parser_parse_from_source_swap(source, NULL);
}

parser * parser_parse_from_source_swap(const char * source, const char * info) {
	parser* p = parser_push(yinput_string);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	if (info != NULL) {
		MEM_FREE(p->source_name);
		p->source_name = text_strdup(info);
	}
	if (text_white(source)) {
		p->root = ast_new_blank();
		return p;
	}
	text_stdout_enabled(false);
	//p->source_name = _strdup("unknown-source");
	yy_setstr(text_strdup(source));
	if (yyparse()) {
		yy_clearstr();
		p->fail = true;
		text_stdout_enabled(true);
		parser_print_error(p);
		//parser_free_source(p);
		return p;
	}
	yy_clearstr();
	text_stdout_enabled(true);
	//parser_free_source(p);
	return p;
}

void parser_swap_source_name(char * source_name) {
	parser* p = parser_top();
	MEM_FREE(p->source_name);
	p->source_name = text_strdup(source_name);
}

void parser_print_error(parser * p) {
	if (!p->fail) {
		return;
	}
	//system("cls");
	//put filename
	text_printf("file=%s ", p->source_name);
	//put line
	text_printf("line=%d ", p->error_line_index);
	//put column
	text_printf("column=%d", p->error_column_index);
	text_putline();
	//put str
	text_printf("%s", p->error_message);
	text_putline();
	//put line
	text_printf("%s", p->error_line_text);
	text_putline();
	fflush(stdout);
	MEM_FREE(p->error_message);
	MEM_FREE(p->error_line_text);
	p->error_message = NULL;
	p->error_line_text = NULL;
}

void parser_pop() {
	script_context* ctx = script_context_get_current();
	parser* p = (parser*)stack_pop(ctx->parser_stack);
	if (p->root) {
		ast_delete(p->root);
	}
	vector_delete(p->lineno_vec, vector_deleter_null);
	MEM_FREE(p->literal_buffer);
	MEM_FREE(p->source_name);
	MEM_FREE(p);
	if (stack_empty(ctx->parser_stack)) {
		stack_delete(ctx->parser_stack, stack_deleter_null);
		ctx->parser_stack = NULL;
	}
}
