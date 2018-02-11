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
	if (ctx->parserStack == NULL) {
		ctx->parserStack = stack_new();
	}
	parser* p = (parser*)MEM_MALLOC(sizeof(parser));
	stack_push(ctx->parserStack, p);
	p->input_type = input_type;
	p->lineno = 0;
	p->linenoVec = vector_new();
	p->root = ast_new(ast_root);
	p->sBuffer = NULL;
	p->errorLineIndex = 0;
	p->errorLineText = NULL;
	p->errorColumnIndex = 0;
	p->errorMessage = NULL;
	p->source_name = text_strdup("unknown-source");
	p->fail = false;
	return p;
}

parser * parser_top() {
	script_context* ctx = script_context_get_current();
	if (ctx->parserStack == NULL) {
		return NULL;
	}
	if (stack_empty(ctx->parserStack)) {
		return NULL;
	}
	return (parser*)stack_top(ctx->parserStack);
}

void parser_clear_buffer(parser * self) {
	self->sBuffer = NULL;
}

void parser_append_buffer(parser * self, char ch) {
	if (self->sBuffer == NULL) {
		self->sBuffer = string_buffer_new();
	}
	string_buffer_append(self->sBuffer, ch);
}

ast * parser_reduce_buffer(parser * self) {
	string_buffer_shrink(self->sBuffer);
	ast* ret = ast_new_string(self->sBuffer->text);
	self->sBuffer->text = NULL;
	MEM_FREE(self->sBuffer);
	self->sBuffer = NULL;
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
	if (yyparse()) {
		p->fail = true;
		parser_print_error(p);
		return p;
	}
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
	//p->source_name = _strdup("unknown-source");
	yy_setstr(text_strdup(source));
	if (yyparse()) {
		yy_clearstr();
		p->fail = true;
		parser_print_error(p);
		//parser_free_source(p);
		return p;
	}
	yy_clearstr();
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
	text_printf("line=%d ", p->errorLineIndex);
	//put column
	text_printf("column=%d", p->errorColumnIndex);
	text_putline();
	//put str
	text_printf("%s", p->errorMessage);
	text_putline();
	//put line
	text_printf("%s", p->errorLineText);
	text_putline();
	fflush(stdout);
	MEM_FREE(p->errorMessage);
	MEM_FREE(p->errorLineText);
	p->errorMessage = NULL;
	p->errorLineText = NULL;
}

void parser_pop() {
	script_context* ctx = script_context_get_current();
	parser* p = (parser*)stack_pop(ctx->parserStack);
	if (p->root) {
		ast_delete(p->root);
	}
	vector_delete(p->linenoVec, vector_deleter_null);
	MEM_FREE(p->sBuffer);
	MEM_FREE(p->source_name);
	MEM_FREE(p);
	if (stack_empty(ctx->parserStack)) {
		stack_delete(ctx->parserStack, stack_deleter_null);
		ctx->parserStack = NULL;
	}
}
