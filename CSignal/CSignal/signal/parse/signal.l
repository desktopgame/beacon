%{
//http://kmaebashi.com/programmer/devlang/diksam.html
#undef YY_INPUT
#define YY_INPUT(buf, result, max_size) (result = my_yyinput(buf, max_size))
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signal.tab.h"
#include "parser.h"
#include "../ast/ast.h"

//for C4996
#ifdef _MSC_VER
#pragma warning(disable:4996)
#elif
#pragma warning(disable:4996)
#endif

int yymain(void) {
	yyparse();
	return(0);
}

int yywrap(void) {
	return 1;
}

int yyerror(char * err_str) {
/*
	fprintf(stderr,err_str);
	printf("\n");
	printf("file-name=%s", get_compiler()->file_name);
	printf(" row=%d", get_compiler()->row);
	printf(" col=%d", 0);
	printf("\n");
*/
	fprintf(stderr,err_str);
}

void yyexit() {
}

static int file_input(char *buf, int max_size) {
	int ch;
	int len;

	if (feof(yyin)) {
		return 0;
	}

	for (len = 0; len < max_size; len++) {
		ch = getc(yyin);
		if (ch == EOF)
			break;
		buf[len] = ch;
	}
    return len;
}

static char* yaccSourceBuffer;
static int yaccSourceOffset;
 
void yy_setstr(char* source) {
	yaccSourceBuffer = source;
	yaccSourceOffset = 0;
}

void yy_clearstr() {
	free(yaccSourceBuffer);
	yaccSourceBuffer = NULL;
	yaccSourceOffset = 0;
}

static int string_input(char *buf, int max_size) {
	int len = 0;
	int startOffset = yaccSourceOffset;
	for(; (yaccSourceOffset < yaccSourceOffset + max_size); yaccSourceOffset++) {
		if(yaccSourceBuffer[yaccSourceOffset] == '\0') {
			break;
		}
		buf[yaccSourceOffset - startOffset] = yaccSourceBuffer[yaccSourceOffset];
		len++;
	}
	return len;
}

static int my_yyinput(char *buf, int max_size) {
	int result;
	parser* p = parser_top();
	switch (p->input_type) {
		case yinput_file:
			result = file_input(buf, max_size);
			break;
		case yinput_string:
			result = string_input(buf, max_size);
			break;
		default:
			return 0;
	}
	return result;
}
%}

%option yy_scan_string
%option yy_scan_buffer
%option yy_scan_bytes
%%
<INITIAL>"."				{ return (DOT); }
<INITIAL>","				{ return (COMMA); }
<INITIAL>":"				{ return (COLON); }
<INITIAL>"::"				{ return (COLO_COLO); }
<INITIAL>";"				{ return (SEMI); }


<INITIAL>"+"				{ return (ADD); }
<INITIAL>"-"				{ return (SUB); }
<INITIAL>"*"				{ return (MUL); }
<INITIAL>"/"				{ return (DIV); }
<INITIAL>"%"				{ return (MOD); }
<INITIAL>"!"				{ return (NOT); }


<INITIAL>"="				{ return (ASSIGN); }
<INITIAL>"+="				{ return (ADD_ASSIGN); }
<INITIAL>"-="				{ return (SUB_ASSIGN); }
<INITIAL>"*="				{ return (MUL_ASSIGN); }
<INITIAL>"/="				{ return (DIV_ASSIGN); }
<INITIAL>"%="				{ return (MOD_ASSIGN); }

<INITIAL>"=="				{ return (EQUAL); }
<INITIAL>"!="				{ return (NOTEQUAL); }


<INITIAL>"++"				{ return (INC); }
<INITIAL>"--"				{ return (DEC); }

<INITIAL>">"				{ return (GT); }
<INITIAL>">="				{ return (GE); }
<INITIAL>"<"				{ return (LT); }
<INITIAL>"<="				{ return (LE); }

<INITIAL>"&"				{ return (BIT_AND); }
<INITIAL>"&&"			{ return (LOGIC_AND); }
<INITIAL>"|"				{ return (BIT_OR); }
<INITIAL>"||"			{ return (LOGIC_OR); }


<INITIAL>"{"				{ return (LCB); }
<INITIAL>"}"				{ return (RCB); }
<INITIAL>"("				{ return (LRB); }
<INITIAL>")"				{ return (RRB); }
<INITIAL>"["				{ return (LSB); }
<INITIAL>"]"				{ return (RSB); }

<INITIAL>"0" {
	yylval.ast_value = ast_new_int(0);
	return INT;
}

<INITIAL>[1-9][0-9]* {
	yylval.ast_value = ast_new_int(atoi(yytext));
	return INT;
}

<INITIAL>[0-9]+\.[0-9]+ {
	yylval.ast_value = ast_new_double(atof(yytext));
	return DOUBLE;
}

<INITIAL>[A-Za-z_][A-Za-z_0-9]* {
	yylval.string_value = _strdup(yytext);
	return IDENT;
}
%%