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


//static stack* parser_stack = NULL;

parser * parser_push(yacc_input_type input_type) {
	script_context* ctx = script_context_get_current();
	if (ctx->parserStack == NULL) {
		ctx->parserStack = stack_new();
	}
	parser* p = (parser*)MEM_MALLOC(sizeof(parser));
	stack_push(ctx->parserStack, p);
	p->input_type = input_type;
	p->root = ast_new(ast_root);
	p->buffer = NULL;
	p->errorLineIndex = 0;
	p->errorColumnIndex = 0;
	p->source_name = text_strdup("unknown-source");
	p->fail = false;
	return p;
}

parser * parser_top() {
	script_context* ctx = script_context_get_current();
	if (ctx->parserStack == NULL) {
		return NULL;
	}
	return (parser*)stack_top(ctx->parserStack);
}

void parser_clear_buffer(parser * self) {
	self->buffer = NULL;
}

void parser_append_buffer(parser * self, char ch) {
	if (self->buffer == NULL) {
		self->buffer = (char*)MEM_MALLOC(sizeof(char) + 1);
		self->buffer[0] = ch;
		self->buffer[1] = '\0';
	} else {
		int len = strlen(self->buffer);
		char* temp = (char*)MEM_REALLOC(self->buffer, (sizeof(char) * (len + 1)) + 0);
		assert(temp != NULL);
		temp[len] = ch;
		temp[len + 1] = '\0';
		self->buffer = temp;
	}
}

ast * parser_reduce_buffer(parser * self) {
	ast* ret = ast_new_string(self->buffer);
	self->buffer = NULL;
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
		return p;
	}
	return p;
#endif
}

parser * parser_parse_from_source(char * source) {
	parser* p = parser_push(yinput_string);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	//p->source_name = _strdup("unknown-source");
	yy_setstr(text_strdup(source));
	if (yyparse()) {
		yy_clearstr();
		p->fail = true;
		return p;
	}
	yy_clearstr();
	return p;
}

void parser_swap_source_name(char * source_name) {
	parser* p = parser_top();
	MEM_FREE(p->source_name);
	p->source_name = text_strdup(source_name);
}

void parser_pop() {
	script_context* ctx = script_context_get_current();
	parser* p = (parser*)stack_pop(ctx->parserStack);
	if (p->root) {
		ast_delete(p->root);
	}
	MEM_FREE(p->buffer);
	MEM_FREE(p->source_name);
	MEM_FREE(p);
	if (stack_empty(ctx->parserStack)) {
		stack_delete(ctx->parserStack, stack_deleter_null);
		ctx->parserStack = NULL;
	}
}
