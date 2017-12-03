#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/stack.h"

static stack* parser_stack = NULL;

parser * parser_push(yacc_input_type input_type) {
	if (parser_stack == NULL) {
		parser_stack = stack_new();
	}
	parser* p = (parser*)malloc(sizeof(parser));
	stack_push(parser_stack, p);
	p->input_type = input_type;
	p->root = ast_new(ast_root);
	p->fail = false;
	return p;
}

parser * parser_top() {
	if (parser_stack == NULL) {
		return NULL;
	}
	return (parser*)stack_top(parser_stack);
}

parser * parser_parse_from_file(const char * filename) {
	extern int yyparse(void);
	extern FILE *yyin;

	parser* p = parser_push(yinput_file);
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
}

parser * parser_parse_from_source(char * source) {
	parser* p = parser_push(yinput_string);
	extern void yy_setstr(char *source);
	extern void yy_clearstr();
	extern int yyparse(void);
	yy_setstr(source);
	if (yyparse()) {
		yy_clearstr();
		p->fail = true;
		return p;
	}
	yy_clearstr();
	return p;
}

void parser_pop() {
	parser* p = (parser*)stack_pop(parser_stack);
	if (p->root) {
		ast_delete(p->root);
	}
	free(p);
	if (stack_empty(parser_stack)) {
		stack_delete(parser_stack, stack_deleter_null);
		parser_stack = NULL;
	}
}
